#include "ast_debug.hpp"

void ASTDebug::debug_type(const core::node::TypeNode *node) {
  out << "Type\n";

  debug_node(node->id, true);

  size_t count = node->generics.size();
  for (size_t i = 0; i < count; ++i) { debug_node(node->generics[i], i == count - 1); }
}
