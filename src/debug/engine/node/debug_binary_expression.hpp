#pragma once
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include <string>

static void debug_binary_expression(const parser::node::BinaryExpressionNode *bin_node, const std::string &prefix, bool isLast) {
  using namespace debug;

  node::print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "BinaryExpression: ", Color::Purple);

  auto child_prefix = node::next_prefix(prefix, isLast);

  node::debug_node(bin_node->left, child_prefix, false);
  node::debug_node(bin_node->right, child_prefix, true);
}
