#pragma once
#include "DebugNode.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"

#include "engine/parser/node/statement_nodes.hpp"
static void debug_block_node(const parser::node::BlockNode *node, const std::string &prefix, bool isLast) {
  using namespace debug;
  using namespace debug::node;

  print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "Block: ");

  std::string child_prefix = next_prefix(prefix, isLast);

  size_t n = node->statements.size();
  for (size_t i = 0; i < n; i++) {
    bool last = (i == n - 1); // calcula se é o último filho
    debug_child("Statement", node->statements[i], child_prefix, last);
  }
}
