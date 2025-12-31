#pragma once

#include "core/source/TextStream.hpp"
#include "engine/CompilationUnit.hpp"
#include "utils/Unicode.hpp"

namespace lexer::match {

inline core::token::Token *match_identifier(CompilationUnit &unit,
                                            core::source::TextStream &stream) {
  auto c = stream.peek();
  auto start = stream.get_state();

  if (!utils::Unicode::is_alpha(c) && c != U'_') {
    return nullptr;
  }

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

  auto slice = stream.slice_from(start);

  auto descriptor =
      unit.context.alias_table.resolve_identifier(slice.span.view());

  if (!descriptor) {
    descriptor = unit.context.descriptor_table.lookup_by_kind(
        core::token::TokenKind::Identifier);
  }

  return unit.tokens.create_token<core::token::Token>(descriptor, slice);
}

} // namespace lexer::match
