#pragma once
#include "DebugNode.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement_nodes.hpp"

static void debug_member_access(const parser::node::MemberAccessNode *node,
                                const std::string &prefix, bool isLast) {
  using namespace debug;

  debug::node::print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "MemberAccess");

  auto child_prefix = node::next_prefix(prefix, isLast);

  // Object
  if (node->object) {
    debug::node::print_prefix(child_prefix, false);
    Console::log("Object:");
    debug::node::debug_node(node->object,
                            node::next_prefix(child_prefix, false), true);
  }

  // Property
  if (node->property) {
    debug::node::print_prefix(child_prefix, true);
    Console::log("Property:");
    debug::node::debug_node(node->property,
                            node::next_prefix(child_prefix, true), true);
  }
}
