#pragma once
#include <cstddef>
#include <string>
#include <string_view>

struct U32Hash {
  using is_transparent = void;

  size_t operator()(std::u32string_view v) const noexcept {
    size_t h = 0;
    for (char32_t c : v) h = h * 131 + static_cast<size_t>(c);
    return h;
  }

  size_t operator()(const std::u32string &v) const noexcept { return operator()(std::u32string_view{v}); }
};

struct U32Equal {
  using is_transparent = void;

  bool operator()(std::u32string_view a, std::u32string_view b) const noexcept { return a == b; }

  bool operator()(const std::u32string &a, const std::u32string &b) const noexcept { return a == b; }

  bool operator()(const std::u32string &a, std::u32string_view b) const noexcept { return a == b; }

  bool operator()(std::u32string_view a, const std::u32string &b) const noexcept { return a == b; }
};
