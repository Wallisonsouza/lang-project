#pragma once
#include <cstdint>
#include <string>
#include <string_view>

namespace utils {

class Utf {
public:
  static bool utf8_to_utf32(const std::string &s,
                            std::u32string &out) noexcept {
    out.clear();
    size_t i = 0;

    if (s.size() >= 3 && (uint8_t)s[0] == 0xEF && (uint8_t)s[1] == 0xBB &&
        (uint8_t)s[2] == 0xBF) {
      i = 3;
    }

    while (i < s.size()) {
      uint8_t c = static_cast<uint8_t>(s[i]);
      uint32_t cp = 0;
      size_t nbytes = 0;

      if ((c & 0x80) == 0) {
        cp = c;
        nbytes = 1;
      } else if ((c & 0xE0) == 0xC0) {
        if (i + 1 >= s.size()) return false;
        cp = ((c & 0x1F) << 6) | (s[i + 1] & 0x3F);
        nbytes = 2;
      } else if ((c & 0xF0) == 0xE0) {
        if (i + 2 >= s.size()) return false;
        cp = ((c & 0x0F) << 12) | ((s[i + 1] & 0x3F) << 6) | (s[i + 2] & 0x3F);
        nbytes = 3;
      } else if ((c & 0xF8) == 0xF0) {
        if (i + 3 >= s.size()) return false;
        cp = ((c & 0x07) << 18) | ((s[i + 1] & 0x3F) << 12) |
             ((s[i + 2] & 0x3F) << 6) | (s[i + 3] & 0x3F);
        nbytes = 4;
      } else {
        return false;
      }

      for (size_t j = 1; j < nbytes; ++j) {
        if ((uint8_t)s[i + j] >> 6 != 0b10) return false;
      }

      out.push_back(cp);
      i += nbytes;
    }

    return true;
  }

  static std::u32string utf8_to_utf32(const std::string &s) noexcept {
    std::u32string out;
    utf8_to_utf32(s, out);
    return out;
  }

  // [[nodiscard]] static std::u32string utf8to32(const std::string &s) noexcept
  // {
  //   std::u32string result;
  //   size_t i = 0;

  //   while (i < s.size()) {
  //     uint8_t c = static_cast<uint8_t>(s[i]);
  //     uint32_t cp = 0;
  //     size_t nbytes = 0;

  //     if ((c & 0x80) == 0) {
  //       cp = c;
  //       nbytes = 1;
  //     } else if ((c & 0xE0) == 0xC0 && i + 1 < s.size()) {
  //       cp = ((c & 0x1F) << 6) | (s[i + 1] & 0x3F);
  //       nbytes = 2;
  //     } else if ((c & 0xF0) == 0xE0 && i + 2 < s.size()) {
  //       cp = ((c & 0x0F) << 12) | ((s[i + 1] & 0x3F) << 6) | (s[i + 2] &
  //       0x3F); nbytes = 3;
  //     } else if ((c & 0xF8) == 0xF0 && i + 3 < s.size()) {
  //       cp = ((c & 0x07) << 18) | ((s[i + 1] & 0x3F) << 12) | ((s[i + 2] &
  //       0x3F) << 6) | (s[i + 3] & 0x3F); nbytes = 4;
  //     } else {
  //       ++i;
  //       continue;
  //     }

  //     result.push_back(cp);
  //     i += nbytes;
  //   }

  //   return result;
  // }

  static void encode(uint32_t cp, std::string &out) {
    if (cp <= 0x7F) {
      out.push_back(static_cast<char>(cp));
    } else if (cp <= 0x7FF) {
      out.push_back(static_cast<char>(0xC0 | ((cp >> 6) & 0x1F)));
      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    } else if (cp <= 0xFFFF) {
      out.push_back(static_cast<char>(0xE0 | ((cp >> 12) & 0x0F)));
      out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    } else if (cp <= 0x10FFFF) {
      out.push_back(static_cast<char>(0xF0 | ((cp >> 18) & 0x07)));
      out.push_back(static_cast<char>(0x80 | ((cp >> 12) & 0x3F)));
      out.push_back(static_cast<char>(0x80 | ((cp >> 6) & 0x3F)));
      out.push_back(static_cast<char>(0x80 | (cp & 0x3F)));
    }
  }

  static std::string utf32to8(const std::u32string_view &text) {
    std::string out;
    out.reserve(text.size() * 4);
    for (uint32_t cp : text) encode(cp, out);
    return out;
  }
};

} // namespace utils
