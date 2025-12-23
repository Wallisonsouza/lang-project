#pragma once

#include "core/node/NodeKind.hpp"
#include "debug/node/debug_function_nodes.hpp"
#include "debug/node/debug_import_node.hpp"
#include "debug_common.hpp"
#include "debug_literal_nodes.hpp"
#include "debug_type_nodes.hpp"
#include "debug_variable_nodes.hpp"

namespace debug::node {

inline void print_node(core::node::Node *node, const std::string &prefix = "",
                       bool isLast = true) {
  if (!node) {
    return;
  }

  print_variable(node, prefix, isLast);
  print_import_node(node, prefix, isLast);
  print_literal_node(node, prefix, isLast);
  print_type_node(node, prefix, isLast);
}

} // namespace debug::node
