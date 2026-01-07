#pragma once
#include "core/AST.hpp"
#include "core/node/Node.hpp"
#include "debug/console/console.hpp"
#include <string>

namespace debug::node {
void debug_node(const core::node::Node *node, const std::string &prefix = "", bool isLast = false);

void print_prefix(const std::string &prefix, bool isLast);

std::string next_prefix(const std::string &prefix, bool isLast);

inline void dump_ast(AST &ast) {

  for (auto &node : ast.get_nodes()) { debug_node(node); }
}

} // namespace debug::node
template <typename NodePtr> void debug_child(const char *label, NodePtr child, const std::string &prefix, bool isLast) {
  if (!child) return;
  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(label, ": ");
  debug::node::debug_node(child, debug::node::next_prefix(prefix, isLast), true);
}
