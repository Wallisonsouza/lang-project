#include "lexer.hpp"

core::token::Token *Lexer::match_number(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out) {

  auto start = stream.get_state();

  auto c = stream.peek();

  if (!utils::Unicode::is_digit(c)) { return nullptr; }

  bool has_dot = false;

  while (true) {
    c = stream.peek();
    if (utils::Unicode::is_digit(c)) {
      stream.advance();
    } else if (c == U'.' && !has_dot) {
      has_dot = true;
      stream.advance();
    } else {
      break;
    }
  }

  auto slice = stream.slice_from(start);

  auto descriptor = context.descriptor_table.lookup_by_kind(core::token::TokenKind::NumberLiteral);

  return out.create_token<core::token::Token>(descriptor, slice);
}
