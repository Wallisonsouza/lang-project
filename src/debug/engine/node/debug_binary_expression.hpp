#pragma once
#include "core/node/BinaryOp.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include <string>

static void
debug_binary_expression(const parser::node::BinaryExpressionNode *node,
                        const std::string &prefix, bool isLast) {
  using namespace debug;

  // Cabeçalho da expressão
  node::print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "BinaryExpression: ", Color::Purple,
               core::node::binary_op_to_string(node->op));

  // Prefixo para os filhos
  auto info_prefix = node::next_prefix(prefix, isLast);
  auto child_prefix = node::next_prefix(info_prefix, isLast);
  // Lado esquerdo
  node::print_prefix(info_prefix, false);
  Console::log(Color::BrightBlue, "Left:");

  debug::node::debug_node(node->left, child_prefix, true);

  // Lado direito
  node::print_prefix(info_prefix, true);
  Console::log(Color::BrightBlue, "Right:");

  debug::node::debug_node(node->right, child_prefix, true);
}
