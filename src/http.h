#ifndef COCOHTTP_HTTP_H
#define COCOHTTP_HTTP_H

#include <cstdint>
#include <optional>
#include <string>
#include <utility>
#include <variant>

namespace cocohttp::http {

enum class message_type { request, response };

// TODO: many have custom format
enum class standard_field {
  accept,
  accept_charset,
  accept_encoding,
  accept_language,
  accept_ranges,
  allow,
  authentication_info,
  authorization,
  connection,
  content_encoding,
  content_language,
  content_length,
  content_location,
  content_range,
  content_type,
  etag,
  expect,
  from,
  host,
  if_match,
  if_modified_since,
  if_none_match,
  if_range,
  if_unmodified_since,
  keep_alive,
  last_modified,
  location,
  max_forwards,
  proxy_authenticate,
  proxy_authentication_info,
  proxy_authorization,
  proxy_connection,
  range,
  referer,
  retry_after,
  server,
  te,
  transfer_encoding,
  upgrade,
  user_agent,
  vary,
  via,
  www_authenticate,
};

using field_name = std::variant<standard_field, std::string>;

using field_value = std::string;

template <typename Tk, typename Tv> class insertion_order_multimap {};

template <typename Tk, typename Tv>
using field_map = insertion_order_multimap<Tk, Tv>;

template <typename Control, typename Content> struct message {
  Control control;
  field_map<field_name, field_value> headers;
  Content content;
  field_map<field_name, field_value> trailers;
};

enum class standard_method {
  get,
  head,
  post,
  put,
  del,
  connect,
  options,
  trace
};

using method = std::variant<standard_method, std::string>;

using uri = std::string;

enum class proto_version { v1, v2 };

struct request_control {
  method method;
  uri target;
  proto_version version;
};

enum class standard_status_code {
  continue_ = 100,
  switching_protocols = 101,
  ok = 200,
  created = 201,
  accepted = 202,
  non_authoritative_information = 203,
  no_content = 204,
  reset_content = 205,
  partial_content = 206,
  multiple_choices = 300,
  moved_permanently = 301,
  found = 302,
  see_other = 303,
  not_modified = 304,
  use_proxy = 305,
  temporary_redirect = 307,
  permanent_redirect = 308,
  bad_request = 400,
  unauthorized = 401,
  payment_required = 402,
  forbidden = 403,
  not_found = 404,
  method_not_allowed = 405,
  not_acceptable = 406,
  proxy_authentication_required = 407,
  request_timeout = 408,
  conflict = 409,
  gone = 410,
  length_required = 411,
  precondition_failed = 412,
  content_too_large = 413,
  uri_too_long = 414,
  unsupported_media_type = 415,
  range_not_satisfiable = 416,
  expectation_failed = 417,
  misdirected_request = 421,
  unprocessable_content = 422,
  upgrade_required = 426,
  internal_server_error = 500,
  not_implemented = 501,
  bad_gateway = 502,
  service_unavailable = 503,
  gateway_timeout = 504,
  http_version_not_supported = 505,
};

struct custom_status_code {
  std::uint16_t code;
  std::string description;

public:
  static custom_status_code create(std::uint16_t code_,
                                   std::string description) noexcept;

private:
  custom_status_code(std::uint16_t code_, std::string description_)
      : code(code_), description(std::move(description_)) {}
};

using status_code = std::variant<standard_status_code, custom_status_code>;

struct response_control {
  status_code status;
  proto_version version;
};

template <typename Content> using request = message<request_control, Content>;

template <typename Content> using response = message<response_control, Content>;
} // namespace cocohttp::http

#endif // COCOHTTP_HTTP_H
