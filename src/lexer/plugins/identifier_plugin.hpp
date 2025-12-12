#pragma once

#include "core/text/TextStream.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "helper/TokenMatchHelper.hpp"
#include "lexer/plugin.hpp"
#include "utils/Unicode.hpp"
#include <optional>

namespace lexer::plugins {

class IdentifierPlugin : public lexer::LexerPlugin {
public:
  std::optional<core::token::Token> match(core::text::TextStream &stream,
                                          core::LangData &data) override {
    auto initial_state = stream.get_state();

    char32_t ch = stream.peek();

    if (!is_valid_start_char(ch)) {
      return std::nullopt;
    }

    stream.advance();

    while (!stream.eof() && is_valid_continue_char(stream.peek())) {
      stream.advance();
    }

    auto final_state = stream.get_state();
    auto span = stream.span_from(initial_state, final_state);

    core::token::TokenDescriptor *desc =
        helper::TokenMatchHelper::resolve_descriptor(data, span);

    if (!desc || desc->group == core::token::TokenGroup::Literal ||
        desc->group == core::token::TokenGroup::Operator) {
      desc =
          data.token_table.lookup_by_kind(core::token::TokenKind::Identifier);
    }

    return core::token::Token(desc, span);
  }

private:
  static bool is_valid_special_char(char32_t c) { return c == U'_'; }
  static bool is_valid_start_char(char32_t c) {
    return utils::Unicode::is_alpha(c) || is_valid_special_char(c);
  }
  static bool is_valid_continue_char(char32_t c) {
    return is_valid_start_char(c) || utils::Unicode::is_digit(c);
  }
};

} // namespace lexer::plugins
