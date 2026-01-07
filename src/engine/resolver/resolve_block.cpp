#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_block(parser::node::BlockNode *node) {
  if (!node) return;

  // resolver.enter_scope();

  for (auto &statement : node->statements) { resolve(statement); }

  // resolver.exit_scope();
}