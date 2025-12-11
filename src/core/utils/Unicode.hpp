#pragma once
#include <string>
#include <unicode/uchar.h>
#include <unicode/urename.h>

namespace interpreter::utils {

class Unicode {
public:
  inline static void trim_u32string(std::u32string &s) {
    s.erase(s.begin(), std::ranges::find_if(s.begin(), s.end(), [](char32_t ch) { return !isWhiteSpace(ch); }));
    s.erase(std::ranges::find_if(s.rbegin(), s.rend(), [](char32_t ch) { return !isWhiteSpace(ch); }).base(), s.end());
  }

  inline static bool is_alpha(char32_t cp) { return u_isUAlphabetic(cp); }

  inline static bool is_letter(char32_t cp) { return (cp >= 0x61 && cp <= 0x7A) || (cp >= 0x41 && cp <= 0x5A); }

  inline static bool is_digit(char32_t cp) { return (cp >= 0x30 && cp <= 0x39); }

  inline static bool is_alphanumeric(char32_t cp) { return is_letter(cp) || is_digit(cp); }

  inline static bool isWhiteSpace(char32_t cp) { return u_isUWhiteSpace(cp); }

  static bool isDigit(char32_t c) { return u_isdigit(c); }

  inline static bool isSymbol(char32_t cp) {

    UCharCategory cat = static_cast<UCharCategory>(u_charType(cp));

    return cat == U_MATH_SYMBOL || cat == U_CURRENCY_SYMBOL || cat == U_MODIFIER_SYMBOL || cat == U_OTHER_SYMBOL;
  }
};

} // namespace interpreter::utils
