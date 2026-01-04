
#pragma once

#include "Resolver.hpp"
#include "engine/parser/node/operator_nodes.hpp"

namespace resolver {

inline void
resolve_binary_expression(CompilationUnit &unit, Resolver &resolver,
                          parser::node::BinaryExpressionNode *node) {
  if (!node) {
    return;
  }

  resolver.resolve(unit, node->left);
  resolver.resolve(unit, node->right);
}

} // namespace resolver