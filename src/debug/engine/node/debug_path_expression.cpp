#include "ast_debug.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

void ASTDebug::debug_path_expression(const parser::node::statement::PathExprNode *node) {
  out << "Path\n";

  size_t count = node->segments.size();
  for (size_t i = 0; i < count; ++i) { debug_node(node->segments[i], i == count - 1); }
}
