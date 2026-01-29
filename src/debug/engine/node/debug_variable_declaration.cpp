#include "ast_debug.hpp"

void ASTDebug::debug_variable_declaration(const core::ast::PatternNode *node) {

  out << "VariableDeclaration\n";

  std::vector<LabeledChild> children;

  if (node->identifier) children.push_back({"Identifier", node->identifier});

  if (node->type) children.push_back({"Type", node->type});

  if (node->value) children.push_back({"Value", node->value});

  for (size_t i = 0; i < children.size(); ++i) {

    bool is_last = (i + 1 == children.size());

    debug_labeled(children[i].label, children[i].node, is_last);
  }
}
