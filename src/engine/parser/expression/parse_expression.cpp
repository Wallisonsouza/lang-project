#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_expression() {

  auto *lhs = parse_postfix_expression();
  if (!lhs) return nullptr;

  if (auto *assign = parse_assignment(lhs)) return assign;

  return parse_binary_expression(0, lhs);
}
