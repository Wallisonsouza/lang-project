#include "debug/engine/token/dump_tokens.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/parser.hpp"
#include <iostream>

core::node::ExpressionNode *Parser::parse_expression() {

  auto *lhs = parse_postfix_expression();
  if (!lhs) return nullptr;

  if (auto node = parse_assignment(lhs)) { return node; }

  return parse_binary_expression(0, lhs);
}
