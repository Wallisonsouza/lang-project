#pragma once

#include "core/source/TextStream.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"

namespace lexer::match {

inline core::token::Token *match_string(CompilationUnit &unit,
                                        core::source::TextStream &stream) {
  char32_t quote = stream.peek();

  if (quote != U'"' && quote != U'\'') {
    return nullptr;
  }

  auto start = stream.get_state();
  stream.advance();

  bool escaped = false;
  bool closed = false;

  while (!stream.eof()) {
    char32_t ch = stream.peek();

    if (escaped) {
      escaped = false;
      stream.advance();
      continue;
    }

    if (ch == U'\\') {
      escaped = true;
      stream.advance();
      continue;
    }

    if (ch == quote) {
      closed = true;
      stream.advance();
      break;
    }

    stream.advance();
  }

  auto slice = stream.slice_from(start);

  if (!closed) {

    // unit.diagnostics.error(
    //     "string literal não terminada",
    //     slice.range
    // );

    return nullptr;
  }

  auto descriptor = unit.context.descriptor_table.lookup_by_kind(
      core::token::TokenKind::StringLiteral);

  return unit.tokens.create_token<core::token::Token>(descriptor, slice);
}

} // namespace lexer::match
