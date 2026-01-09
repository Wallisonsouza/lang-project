#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_expression_statement(core::node::ExpressionStatementNode *node) {

  if (node->expr) { resolve(node->expr); }
}
