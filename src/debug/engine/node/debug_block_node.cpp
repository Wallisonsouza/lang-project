#include "ast_debug.hpp"

void ASTDebug::debug_block_node(const parser::node::BlockNode *node) {
  out << "Block\n";

  size_t count = node->statements.size();
  for (size_t i = 0; i < count; ++i) { debug_node(node->statements[i], i == count - 1); }
}