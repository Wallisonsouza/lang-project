#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "debug/engine/node/ast_debug.hpp"
#include <vector>

void ASTDebug::debug_function_declaration(const parser::node::FunctionDeclarationNode *node) {

  out << "FunctionDeclarationNode\n";

  if (node->identifier) { debug_node(node->identifier, false); }

  if (!node->params.empty()) { debug_labeled_childrens(node->params, "Args", node->return_type == nullptr && node->body == nullptr); }

  if (node->return_type) { debug_labeled("ReturnType", node->return_type, node->body == nullptr); }

  if (node->body) { debug_node(node->body, true); }
}

void ASTDebug::debug_funtion_parameter(const core::node::FunctionParameterNode *node) {

  out << "FunctionParameterNode\n";

  std::vector<const core::node::Node *> children;

  if (node->identifier) children.push_back(node->identifier);
  if (node->type) children.push_back(node->type);
  if (node->value) children.push_back(node->value);

  for (size_t i = 0; i < children.size(); ++i) {
    bool is_last = (i + 1 == children.size());
    debug_node(children[i], is_last);
  }
}

void ASTDebug::debug_function_call(const parser::node::FunctionCallNode *node) {
  out << "FunctionCall\n";

  if (node->callee) {
    bool callee_is_last = node->args.empty();
    debug_labeled("Callee", node->callee, callee_is_last);
  }

  if (!node->args.empty()) { debug_labeled_childrens(node->args, "Args", true); }
}
