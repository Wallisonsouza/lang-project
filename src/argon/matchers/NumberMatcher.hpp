#pragma once
#include "core/LangData.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "core/utils/Stream.hpp"
#include "core/utils/Unicode.hpp"
#include <memory>

namespace argon::matchers {

class NumberMatcher : public lang::core::Matcher {
public:
  std::shared_ptr<lang::core::Token> match(lang::core::Stream<char32_t> &stream, lang::core::LangData &data) override {

    if (stream.eof()) return nullptr;

    size_t start = stream.get_current_position();

    std::u32string buffer = parse_sign(stream);

    if (stream.eof() || !is_digit(stream.current())) return nullptr;

    buffer += parse_digits_and_dot(stream);

    auto desc = data.token_table.lookup_by_kind(lang::core::TokenKind::Number);
    return std::make_shared<lang::core::Token>(desc, buffer, lang::core::Location{stream.get_current_line(), start, stream.get_current_position()});
  }

private:
  std::u32string parse_sign(lang::core::Stream<char32_t> &stream) {
    std::u32string result;
    if (!stream.eof() && is_sign_char(stream.current())) {
      result.push_back(stream.current());
      stream.consume();
    }
    return result;
  }

  std::u32string parse_digits_and_dot(lang::core::Stream<char32_t> &stream) {
    std::u32string result;
    bool has_dot = false;

    while (!stream.eof()) {
      char32_t c = stream.current();
      if (is_digit(c)) {
        result.push_back(c);
      } else if (is_dot_char(c) && !has_dot) {
        has_dot = true;
        result.push_back(c);
      } else {
        break;
      }
      stream.consume();
    }

    return result;
  }

  static bool is_dot_char(char32_t c) { return c == U'.'; }
  static bool is_digit(char32_t c) { return lang::utils::Unicode::is_digit(c); }
  static bool is_sign_char(char32_t c) { return c == U'+' || c == U'-'; }
};

} // namespace argon::matchers
