#pragma once
#include "core/node/BinaryOp.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include <string>

static void debug_binary_expression(const parser::node::BinaryExpressionNode *node, const std::string &prefix, bool isLast) {
  using namespace debug;

  // Imprime o nó atual
  node::print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "BinaryExpression: ", Color::Purple, core::node::binary_op_to_string(node->op));

  auto child_prefix = node::next_prefix(prefix, isLast);

  // Lado esquerdo
  if (node->left) {
    node::print_prefix(child_prefix, !node->right); // se não houver right, left é último
    Console::log(Color::BrightBlue, "Left:");
    node::debug_node(node->left, node::next_prefix(child_prefix, !node->right), !node->right);
  }

  // Lado direito
  if (node->right) {
    node::print_prefix(child_prefix, true); // sempre último
    Console::log(Color::BrightBlue, "Right:");
    node::debug_node(node->right, node::next_prefix(child_prefix, true), true);
  }
}
