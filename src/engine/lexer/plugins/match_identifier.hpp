#pragma once

#include "core/source/TextStream.hpp"
#include "core/token/TokenGroup.hpp"
#include "engine/CompilationUnit.hpp"
#include "utils/Unicode.hpp"

namespace lexer::match {

inline core::token::Token *match_identifier(CompilationUnit &unit,
                                            core::source::TextStream &stream) {
  auto c = stream.peek();
  auto start = stream.get_state();

  if (!utils::Unicode::is_alpha(c) && c != U'_')
    return nullptr;

  stream.advance();
  while (true) {
    c = stream.peek();
    if (utils::Unicode::is_alpha(c) || utils::Unicode::is_digit(c) ||
        c == U'_') {
      stream.advance();
    } else {
      break;
    }
  }

  auto end = stream.get_state();
  auto span = stream.span_from(start, end);
  auto location = stream.range_from(start, end);

  // Resolve alias
  auto descriptor = unit.context.alias_table.resolve_alias(span.view());
  if (!descriptor || descriptor->group == core::token::TokenGroup::Literal ||
      descriptor->group == core::token::TokenGroup::Operator) {
    descriptor = unit.context.descriptor_table.lookup_by_kind(
        core::token::TokenKind::Identifier);
  }

  return unit.tokens.create_token<core::token::Token>(descriptor, span,
                                                      location);
}

} // namespace lexer::match
