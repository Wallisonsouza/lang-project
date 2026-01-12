#include "ast_debug.hpp"

void ASTDebug::debug_block(const parser::node::BlockExpressionNode *node) {

  out << "Block\n";

  bool has_statements = !node->statements.empty();
  bool has_tail = node->tail_expression != nullptr;

  if (has_statements) { debug_labeled_childrens(node->statements, "Statements", !has_tail); }

  if (has_tail) { debug_labeled("TailExpression", node->tail_expression, true); }
}
