#pragma once
#include "DebugNode.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement_nodes.hpp"

static void debug_if_statement(const parser::node::IfStatementNode *node, const std::string &prefix, bool isLast) {
  using namespace debug;
  using namespace debug::node;

  Console::log(Color::BrightBlue, "If: ");

  // auto child_prefix = next_prefix(prefix, isLast);

  // // Condition
  // if (node->condition) {
  //   // Condition é último se then e else não existirem
  //   bool last_condition = !node->then_body && !node->else_body;
  //   print_prefix(child_prefix, last_condition);
  //   Console::log("Condition: ");
  //   debug_node(node->condition, next_prefix(child_prefix, last_condition), true);
  // }

  // // Then
  // if (node->then_body) {
  //   // Then é último se else não existir
  //   bool last_then = !node->else_body;
  //   print_prefix(child_prefix, last_then);
  //   Console::log("Then: ");
  //   debug_node(node->then_body, next_prefix(child_prefix, last_then), true);
  // }

  // // Else
  // if (node->else_body) {
  //   print_prefix(child_prefix, true); // sempre último
  //   Console::log("Else: ");
  //   debug_node(node->else_body, next_prefix(child_prefix, true), true);
  // }
}
