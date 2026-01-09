#include "ast_debug.hpp"
#include "engine/parser/node/statement_nodes.hpp"

void ASTDebug::debug_function_call(const parser::node::FunctionCallNode *node) {
  out << "FunctionCall\n";

  size_t arg_count = node->args.size();

  if (node->callee) {
    bool callee_is_last = (arg_count == 0);
    debug_node(node->callee, callee_is_last);
  }

  for (size_t i = 0; i < arg_count; ++i) {
    bool is_last = (i + 1 == arg_count);
    debug_node(node->args[i], is_last);
  }
}
