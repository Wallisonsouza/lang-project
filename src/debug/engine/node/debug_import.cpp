#include "ast_debug.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

void ASTDebug::debug_import(const parser::node::statement::ImportNode *node) {
  out << "Import\n";

  size_t count = node->path.size();

  for (size_t i = 0; i < count; ++i) { debug_node(node->path[i], i == count - 1); }
}
