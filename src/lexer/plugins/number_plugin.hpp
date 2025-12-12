#pragma once

#include "core/text/TextStream.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "lexer/plugin.hpp"
#include "utils/Unicode.hpp"

namespace lexer::plugins {
class NumberPlugin : public lexer::LexerPlugin {
public:
  std::optional<core::token::Token> match(core::text::TextStream &stream,
                                          core::LangData &data) override {

    if (stream.eof())
      return std::nullopt;

    auto initial_state = stream.get_state();

    parse_sign(stream);

    if (stream.eof() || !is_digit(stream.peek())) {
      return std::nullopt;
    }

    parse_digits_and_dot(stream);

    auto final_state = stream.get_state();

    auto desc =
        data.token_table.lookup_by_kind(core::token::TokenKind::NumberLiteral);

    auto span = stream.span_from(initial_state, final_state);

    return core::token::Token(desc, span);
  }

private:
  void parse_sign(core::text::TextStream &stream) {
    if (!stream.eof() && is_sign_char(stream.peek())) {
      stream.advance();
    }
  }

  void parse_digits_and_dot(core::text::TextStream &stream) {
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
  static bool is_digit(char32_t c) { return utils::Unicode::is_digit(c); }
  static bool is_sign_char(char32_t c) { return c == U'+' || c == U'-'; }
};

} // namespace lexer::plugins
