#include "ast_debug.hpp"

void ASTDebug::debug_variable_declaration(const parser::node::VariableDeclarationNode *node) {
  out << "VariableDeclaration\n";

  debug_children({node->identifier, node->type, node->value});
}
