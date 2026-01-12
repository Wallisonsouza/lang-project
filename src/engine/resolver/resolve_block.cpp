#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_block(parser::node::BlockExpressionNode *node, bool create_scope) {

  if (create_scope) push_scope();

  for (auto *stmt : node->statements) resolve(stmt);

  if (node->tail_expression) { resolve(node->tail_expression); }

  if (create_scope) pop_scope();
}