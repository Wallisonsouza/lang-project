#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_block(parser::node::BlockNode *node) {
  if (!node) return;

  push_scope();

  for (auto *statement : node->statements) { resolve(statement); }

  pop_scope();
}
