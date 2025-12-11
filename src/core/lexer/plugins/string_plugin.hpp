#pragma once
#include "core/LangData.hpp"
#include "core/lexer/plugin.hpp"
#include "core/token/TokenKind.hpp"

namespace interpreter::lexer::plugins {

class StringPlugin : public interpreter::lexer::LexerPlugin {
public:
  bool match(TextStream &stream, interpreter::core::LangData &data) override {
    if (stream.eof()) return false;

    auto initial_state = stream.get_state();
    char32_t quote = stream.peek();

    if (!is_string_start(quote)) return false;

    stream.advance();

    bool escaped = false;
    while (!stream.eof()) {
      char32_t ch = stream.peek();
      if (escaped) {
        escaped = false;
      } else if (ch == U'\\') {
        escaped = true;
      } else if (ch == quote) {
        break;
      }
      stream.advance();
    }

    auto final_state = stream.get_state();
    if (!stream.eof() && stream.peek() == quote) { stream.advance(); }

    TextSpan span = stream.span_from(initial_state, final_state);

    auto desc = data.token_table.lookup_by_kind(interpreter::core::TokenKind::StringLiteral);
    data.make_token(desc, span);

    return true;
  }

private:
  bool is_string_start(char32_t ch) const { return ch == U'"' || ch == U'\''; }

  std::u32string parse_string_content(TextStream &stream, char32_t quote) {
    std::u32string buffer;
    bool escaped = false;

    while (!stream.eof()) {
      char32_t ch = stream.peek();

      if (escaped) {
        buffer.push_back(parse_escape_sequence(ch));
        escaped = false;
      } else if (ch == U'\\') {
        escaped = true;
      } else if (ch == quote) {
        stream.advance();
        break;
      } else {
        buffer.push_back(ch);
      }

      stream.advance();
    }

    return buffer;
  }

  char32_t parse_escape_sequence(char32_t ch) const {
    switch (ch) {
    case U'n': return U'\n';
    case U't': return U'\t';
    case U'r': return U'\r';
    case U'"': return U'"';
    case U'\'': return U'\'';
    case U'\\': return U'\\';
    default: return ch;
    }
  }
};

} // namespace interpreter::lexer::plugins
