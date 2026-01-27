#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_postfix_expression() {

  auto *expr = parse_primary_expression();
  if (!expr)
    return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok)
      break;

    switch (tok->descriptor->kind) {

    case TokenKind::OpenParen:
      expr = finish_call(expr);
      if (!expr)
        return nullptr;
      break;

    case TokenKind::Dot:

      expr = parse_path_segment(expr);
      if (!expr)
        return nullptr;
      break;

    case TokenKind::OPEN_BRACKET:
      expr = parse_index_access(expr);
      if (!expr)
        return nullptr;
      break;

    default:
      return expr;
    }
  }

  return expr;
}
