#include "http.h"
#include <cassert>

namespace cocohttp::http {

custom_status_code custom_status_code::create(std::uint16_t code_,
                                              std::string description) noexcept {
  assert(code_ >= 0 && code_ < 1000);
  return {code_, std::move(description)};
}
} // namespace cocohttp::http