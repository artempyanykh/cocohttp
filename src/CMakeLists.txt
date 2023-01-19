add_library(cocohttp cocohttp.cpp http.h http.cpp)
target_compile_features(cocohttp PUBLIC cxx_std_20)

find_package(asio CONFIG REQUIRED)
target_link_libraries(cocohttp PRIVATE asio asio::asio)