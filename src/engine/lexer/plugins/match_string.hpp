#pragma once

#include "core/source/TextStream.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"

namespace lexer::match {
inline core::token::Token *match_string(CompilationUnit &unit,
                                        core::source::TextStream &stream) {
  char32_t quote = stream.peek();
  if (quote != U'"' && quote != U'\'')
    return nullptr;

  auto start = stream.get_state();
  stream.advance();

  bool escaped = false;
  while (!stream.eof()) {
    char32_t ch = stream.peek();

    if (escaped) {
      escaped = false;
      stream.advance();
      continue;
    }

    if (ch == U'\\') {
      escaped = true;
    } else if (ch == quote) {
      break;
    }

    stream.advance();
  }

  if (!stream.eof() && stream.peek() == quote)
    stream.advance();

  auto end = stream.get_state();
  auto span = stream.span_from(start, end);
  auto range = stream.range_from(start, end);

  auto descriptor = unit.context.descriptor_table.lookup_by_kind(
      core::token::TokenKind::StringLiteral);
  return unit.tokens.create_token<core::token::Token>(descriptor, span, range);
}

} // namespace lexer::match
