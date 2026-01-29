#include "ast_debug.hpp"
#include "core/node/BinaryOp.hpp"
#include "engine/parser/node/operator_nodes.hpp"

void ASTDebug::debug_binary_expression(const parser::node::BinaryExpressionNode *node) {

  debug_header("BinaryExpression: " + core::ast::binary_op_to_string(node->op));

  if (node->left) { debug_labeled("Left", node->left, false); }

  if (node->right) { debug_labeled("Right", node->right, true); }
}
