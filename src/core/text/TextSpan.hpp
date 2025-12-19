#pragma once
#include <cstddef>
#include <string_view>

#pragma once
#include <string_view>

namespace core::source {

struct Span {
  const char32_t *begin = nullptr;
  const char32_t *end = nullptr;

  constexpr size_t size() const noexcept { return static_cast<size_t>(end - begin); }

  constexpr bool empty() const noexcept { return begin == end; }

  std::u32string_view view() const { return {begin, size()}; }
};

} // namespace core::source
