#include "ast_debug.hpp"

void ASTDebug::debug_assing_node(const parser::node::statement::AssignmentNode *node) {
  out << "Assing\n";

  if (node->target) { debug_labeled("Target", node->target, false); }

  if (node->value) { debug_labeled("Value", node->value, true); }
}