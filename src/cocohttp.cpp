#include <iostream>
#include <format>

#include "asio/io_context.hpp"
#include "asio/signal_set.hpp"
#include "asio/co_spawn.hpp"
#include "asio/detached.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/write.hpp"

#include "cocohttp.h"

namespace cocohttp {
    using asio::co_spawn;
    using asio::awaitable;
    using asio::detached;
    using asio::use_awaitable;
    using asio::ip::tcp;
    using asio::ip::port_type;
    namespace this_coro = asio::this_coro;

    void foo() {
        std::cout << "Hello from cocohttp" << std::endl;
    }

    awaitable<void> echo_ip(tcp::socket socket) {
        auto remote = socket.remote_endpoint();
        auto addr = remote.address().to_string();
        auto buf = asio::buffer(addr);
        co_await asio::async_write(socket, buf, use_awaitable);
    }

    awaitable<void> listener(port_type port) {
        auto executor = co_await this_coro::executor;
        tcp::acceptor acceptor(executor, {tcp::v4(), port});
        for (;;) {
            tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
            co_spawn(executor, echo_ip(std::move(socket)), detached);
        }
    }

    void run_server(uint_least16_t port) {
        try {
            asio::io_context io_context(1);

            asio::signal_set signals(io_context, SIGINT, SIGTERM);
            signals.async_wait([&](auto, auto) { io_context.stop(); });

            co_spawn(io_context, listener(port), detached);

            io_context.run();
        } catch (std::exception& e) {
            std::printf("Exception: %s\n", e.what());
        }
    }

}