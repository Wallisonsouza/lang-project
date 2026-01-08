#pragma once
#include "core/node/BinaryOp.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include <string>

static void debug_binary_expression(const parser::node::BinaryExpressionNode *node, const std::string &prefix, bool isLast) {
  using namespace debug;

  Console::log(Color::BrightBlue, "BinaryExpression: ", Color::Purple, core::node::binary_op_to_string(node->op));

  if (node->left) { debug_child("Left", node->left, prefix, !node->right); }

  if (node->right) { debug_child("Right", node->right, prefix, true); }
}
