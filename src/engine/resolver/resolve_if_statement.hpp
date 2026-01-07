#pragma once

#include "Resolver.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"

namespace resolver {

inline void resolve_if_statement_node(CompilationUnit &unit, Resolver &resolver, parser::node::IfStatementNode *node) {
  if (!node) return;

  if (node->condition) { resolver.resolve(unit, node->condition); }

  if (node->then_body) { resolver.resolve(unit, node->then_body); }

  if (node->else_body) { resolver.resolve(unit, node->else_body); }
}

inline void resolve_block_node(CompilationUnit &unit, Resolver &resolver, parser::node::BlockNode *node) {
  if (!node) return;

  // resolver.enter_scope();

  for (auto &statement : node->statements) { resolver.resolve(unit, statement); }

  // resolver.exit_scope();
}

} // namespace resolver
