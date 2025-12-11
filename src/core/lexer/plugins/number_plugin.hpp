#pragma once
#include "core/LangData.hpp"
#include "core/lexer/plugin.hpp"
#include "core/token/TokenKind.hpp"
#include "core/utils/Unicode.hpp"

namespace interpreter::lexer::plugins {
class NumberPlugin : public interpreter::lexer::LexerPlugin {
public:
  bool match(TextStream &stream, interpreter::core::LangData &data) override {

    if (stream.eof()) return false;

    auto initial_state = stream.get_state();

    parse_sign(stream);

    if (stream.eof() || !is_digit(stream.peek())) { return false; }

    parse_digits_and_dot(stream);

    auto final_state = stream.get_state();

    auto desc = data.token_table.lookup_by_kind(interpreter::core::TokenKind::NumberLiteral);

    auto span = stream.span_from(initial_state, final_state);

    data.make_token(desc, span);

    return true;
  }

private:
  void parse_sign(TextStream &stream) {
    if (!stream.eof() && is_sign_char(stream.peek())) { stream.advance(); }
  }

  void parse_digits_and_dot(TextStream &stream) {
    bool has_dot = false;

    while (!stream.eof()) {
      char32_t c = stream.peek();

      if (is_digit(c)) {
        stream.advance();
      } else if (is_dot_char(c) && !has_dot) {
        has_dot = true;
        stream.advance();
      } else {
        break;
      }
    }
  }

  static bool is_dot_char(char32_t c) { return c == U'.'; }
  static bool is_digit(char32_t c) { return interpreter::utils::Unicode::is_digit(c); }
  static bool is_sign_char(char32_t c) { return c == U'+' || c == U'-'; }
};

} // namespace interpreter::lexer::plugins
