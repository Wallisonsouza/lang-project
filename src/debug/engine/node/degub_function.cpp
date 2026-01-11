#include "core/node/Type.hpp"
#include "debug/engine/node/ast_debug.hpp"

void ASTDebug::debug_function_declaration(const parser::node::FunctionDeclarationNode *node) {
  out << "FunctionDeclaration\n";

  std::vector<const core::node::Node *> children;

  // Identifier
  if (node->identifier) { debug_node(node->identifier, false); }

  // Args (parâmetros)
  if (!node->params.empty()) {

    debug_labeled_childrens(node->params); // passa is_last correto
    // Passa cada FunctionParameterNode para debug_funtion_parameter
    // debug_labeled_childrens("Args", node->params, false);
  }

  // // ReturnType
  // if (node->return_type) {
  //   bool is_last = (node->body == nullptr);
  //   debug_labeled("ReturnType", node->return_type, is_last);
  // }

  // // Body
  // if (node->body) { debug_labeled("Body", node->body, true); }
}

void ASTDebug::debug_funtion_parameter(const core::node::FunctionParameterNode *node) {

  std::vector<std::pair<const char *, const core::node::Node *>> children;
  if (node->identifier) children.push_back({"Identifier", node->identifier});
  if (node->type) children.push_back({"Type", node->type});
  if (node->value) children.push_back({"Value", node->value});

  for (size_t i = 0; i < children.size(); i++) {
    bool is_last = (i == children.size() - 1);
    debug_labeled(children[i].first, children[i].second, is_last);
  }
}

void ASTDebug::debug_function_call(const parser::node::FunctionCallNode *node) {
  // out << "FunctionCall\n";

  // if (node->callee) {
  //   bool callee_is_last = node->args.empty();
  //   debug_labeled("Callee", node->callee, callee_is_last);
  // }

  // if (!node->args.empty()) { debug_labeled_childrens("Args", node->args, true); }
}
