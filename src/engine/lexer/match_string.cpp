#include "lexer.hpp"

core::token::Token *Lexer::match_string(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out) {
  char32_t quote = stream.peek();

  if (quote != U'"' && quote != U'\'') { return nullptr; }

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

    // unit.diagnostics.emit({DiagnosticCode::UnterminatedString, slice});

    return nullptr;
  }

  auto descriptor = context.descriptor_table.lookup_by_kind(core::token::TokenKind::StringLiteral);

  return out.create_token<core::token::Token>(descriptor, slice);
}
