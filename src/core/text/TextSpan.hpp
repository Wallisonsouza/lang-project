#pragma once
#include <cstddef>

struct TextSpan {
  size_t start;
  size_t end;
  size_t line;
  size_t column;
  size_t end_column;

  constexpr TextSpan(size_t s = 0, size_t e = 0, size_t l = 1, size_t c = 1, size_t ec = 1) : start(s), end(e), line(l), column(c), end_column(ec) {}

  constexpr size_t length() const noexcept { return end - start; }
  constexpr bool empty() const noexcept { return start == end; }
};
