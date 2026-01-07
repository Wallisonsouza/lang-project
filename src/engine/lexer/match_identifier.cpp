#include "lexer.hpp"

core::token::Token *Lexer::match_identifier(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out) {

  auto start = stream.get_state();
  char32_t c = stream.peek();

  if (!utils::Unicode::is_alpha(c) && c != U'_') return nullptr;

  stream.advance();

  while (true) {
    c = stream.peek();
    if (utils::Unicode::is_alpha(c) || utils::Unicode::is_digit(c) || c == U'_') {
      stream.advance();
    } else {
      break;
    }
  }

  auto slice = stream.slice_from(start);

  auto descriptor = context.descriptor_table.lookup_by_name(slice.span.view());
  if (!descriptor) { descriptor = context.descriptor_table.lookup_by_kind(core::token::TokenKind::Identifier); }

  return out.create_token<core::token::Token>(descriptor, slice);
}
