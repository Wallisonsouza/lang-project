#pragma once
#include "core/LangData.hpp"
#include "core/TextStream.hpp"
#include "core/helper/TokenMatchHelper.hpp"
#include "core/lexer/plugin.hpp"
#include "core/text/TextStream.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "core/utils/Unicode.hpp"

namespace interpreter::lexer::plugins {

class IdentifierPlugin : public LexerPlugin {
public:
  bool match(TextStream &stream, core::LangData &data) override {
    auto initial_state = stream.get_state();

    char32_t ch = stream.peek();

    if (!is_valid_start_char(ch)) {
      return false;
    }

    stream.advance();

    while (!stream.eof() && is_valid_continue_char(stream.peek())) {
      stream.advance();
    }

    auto final_state = stream.get_state();

    auto span = stream.span_from(initial_state, final_state);

    TokenDescriptor *desc =
        helper::TokenMatchHelper::resolve_descriptor(data, span);

    if (!desc || desc->group == core::TokenGroup::Literal ||
        desc->group == core::TokenGroup::Operator) {
      desc = data.token_table.lookup_by_kind(core::TokenKind::Identifier);
    }

    data.tokens_storage.emplace_back(desc, span);

    return true;
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

} // namespace interpreter::lexer::plugins
