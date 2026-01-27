// #include "engine/lexer/lexer.hpp"

// Token *Lexer::match_comment() {

//   char32_t c = stream.peek();

//   if (c == U'/' && stream.peek_n(1) == U'/') {
//     auto start = stream.get_state();
//     stream.advance_n(2);
//     while (stream.peek() != U'\n' && !stream.eof())
//       stream.advance();
//     auto slice = stream.slice_from(start);
//     auto descriptor = unit.context.descriptor_table.lookup_by_kind(
//         TokenKind::COMMENT);
//     return unit.tokens.create_token<Token>(descriptor, slice);
//   }

//   if (c == U'/' && stream.peek_n(1) == U'*') {
//     auto start = stream.get_state();
//     stream.advance_n(2);
//     while (!stream.eof()) {
//       if (stream.peek() == U'*' && stream.peek_n(1) == U'/') {
//         stream.advance_n(2);
//         break;
//       }
//       stream.advance();
//     }
//     auto slice = stream.slice_from(start);
//     auto descriptor = unit.context.descriptor_table.lookup_by_kind(
//         TokenKind::COMMENT);
//     return unit.tokens.create_token<Token>(descriptor, slice);
//   }

//   return nullptr;
// }