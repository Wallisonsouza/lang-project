#include "ast_debug.hpp"

void ASTDebug::debug_if_statement(const parser::node::IfStatementNode *node) {
  out << "If\n";

  bool has_else = node->else_block != nullptr;

  // Condition
  if (node->condition) { debug_labeled_child("Condition", node->condition, false); }

  // Then
  if (node->then_block) { debug_labeled_child("Then", node->then_block, !has_else); }

  // Else
  if (node->else_block) { debug_labeled_child("Else", node->else_block, true); }
}
