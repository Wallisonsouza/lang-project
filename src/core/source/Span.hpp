#pragma once

#include <string_view>
namespace core::source {

struct Span {
  const char *begin;
  const char *end;

  std::string_view view() const { return std::string_view(begin, end - begin); }
};

} // namespace core::source
