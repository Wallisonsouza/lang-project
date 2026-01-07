#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_if_statement(parser::node::IfStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolve(node->condition); }

  if (node->then_body) { resolve(node->then_body); }

  if (node->else_body) { resolve(node->else_body); }
}
