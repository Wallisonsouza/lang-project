#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_postfix_expression() {

  auto *expr = parse_primary_expression();
  if (!expr)
    return nullptr;

  while (true) {
    auto *tok = stream.peek();
    if (!tok)
      break;

    switch (tok->descriptor->kind) {

    case core::token::TokenKind::OpenParen:
      expr = finish_call(expr);
      break;

    case core::token::TokenKind::Dot:
      // expr = parse_member_access(unit, stream, expr);
      break;

    case core::token::TokenKind::OpenBracket:
      // expr = parse_index_access(unit, stream, expr);
      break;

    default:
      return expr;
    }
  }

  return expr;
}
