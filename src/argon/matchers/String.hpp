#pragma once
#include "core/LangData.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "core/utils/Stream.hpp"
#include <memory>

namespace argon::matchers {

class StringMatcher : public lang::core::Matcher {
public:
  std::shared_ptr<lang::core::Token> match(lang::core::Stream<char32_t> &stream, lang::core::LangData &data) override {
    if (stream.eof()) return nullptr;

    char32_t quote = stream.current();
    if (!is_string_start(quote)) return nullptr;

    size_t start = stream.get_current_position();
    stream.consume();

    std::u32string buffer = parse_string_content(stream, quote);

    auto desc = data.token_table.lookup_by_kind(lang::core::TokenKind::String);
    return std::make_shared<lang::core::Token>(desc, buffer, lang::core::Location{0, start, stream.get_current_position()});
  }

private:
  bool is_string_start(char32_t ch) const { return ch == U'"' || ch == U'\''; }

  std::u32string parse_string_content(lang::core::Stream<char32_t> &stream, char32_t quote) {
    std::u32string buffer;
    bool escaped = false;

    while (!stream.eof()) {
      char32_t ch = stream.current();

      if (escaped) {
        buffer.push_back(parse_escape_sequence(ch));
        escaped = false;
      } else if (ch == U'\\') {
        escaped = true;
      } else if (ch == quote) {
        stream.consume();
        break;
      } else {
        buffer.push_back(ch);
      }

      stream.consume();
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

} // namespace argon::matchers
