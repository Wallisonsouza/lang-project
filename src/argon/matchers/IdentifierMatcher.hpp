#pragma once
#include "core/LangData.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "core/utils/Stream.hpp"
#include "core/utils/Unicode.hpp"
#include <memory>

namespace argon::matchers {

class IdentifierMatcher : public lang::core::Matcher {
public:
  std::shared_ptr<lang::core::Token> match(lang::core::Stream<char32_t> &stream, lang::core::LangData &data) override {

    if (stream.eof()) { return nullptr; }

    size_t start = stream.get_current_position();
    char32_t ch = stream.current();

    if (!is_valid_start_char(ch)) { return nullptr; }

    std::u32string buffer;
    buffer.push_back(ch);
    stream.consume();

    while (!stream.eof()) {
      char32_t c = stream.current();
      if (!is_valid_continue_char(c)) { break; }

      buffer.push_back(c);
      stream.consume();
    }

    if (TokenDescriptor *alias = data.alias_table.lookup_by_name(buffer)) {
      return std::make_shared<lang::core::Token>(alias, buffer, lang::core::Location{stream.get_current_line(), start, stream.get_current_position()});
    }

    if (TokenDescriptor *keyword = data.token_table.lookup_by_name(buffer)) {
      return std::make_shared<lang::core::Token>(keyword, buffer, lang::core::Location{stream.get_current_line(), start, stream.get_current_position()});
    }

    TokenDescriptor *desc = data.token_table.lookup_by_kind(lang::core::TokenKind::Identifier);

    return std::make_shared<lang::core::Token>(desc, buffer, lang::core::Location{stream.get_current_line(), start, stream.get_current_position()});
  }

private:
  static bool is_valid_special_char(char32_t c) { return c == U'_'; }

  static bool is_valid_start_char(char32_t c) { return lang::utils::Unicode::is_alpha(c) || is_valid_special_char(c); }

  static bool is_valid_continue_char(char32_t c) { return is_valid_start_char(c) || lang::utils::Unicode::is_digit(c); }
};

} // namespace argon::matchers
