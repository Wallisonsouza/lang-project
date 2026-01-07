#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_postfix_expression() {

  auto *expr = parse_primary_expression();
  if (!expr) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok) break;

    switch (tok->descriptor->kind) {

    case core::token::TokenKind::OpenParen: expr = finish_call(expr); break;

    case core::token::TokenKind::Dot:
      // expr = parse_member_access(unit, unit.tokens, expr);
      break;

    case core::token::TokenKind::OpenBracket:
      // expr = parse_index_access(unit, unit.tokens, expr);
      break;

    default: return expr;
    }
  }

  return expr;
}
