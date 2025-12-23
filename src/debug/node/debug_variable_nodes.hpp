#pragma once
#include "core/node/Node.hpp"
#include "core/node/NodeKind.hpp"
#include "debug/console/console.hpp"
#include "debug/node/debug_common.hpp"
#include "debug/node/debug_node_helpers.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "utils/Utf8.hpp"
#include <string>

namespace debug::node {

inline void print_variable(core::node::Node *node,
                           const std::string &prefix = "", bool isLast = true) {
  if (!node)
    return;

  if (node->kind != core::node::NodeKind::VariableDeclaration)
    return;

  auto *var = static_cast<parser::node::VariableDeclarationNode *>(node);

  Console::log(prefix, connector(isLast),
               "VariableDeclaration: ", utils::Utf::utf32to8(var->name));

  std::string childPrefix = prefix + child_prefix(isLast);

  Console::log(childPrefix, connector(false),
               "Modifiers: ", core::node::modifiersToString(var->modifiers));

  Console::log(childPrefix, connector(false), "Type:");
  print_node(var->type, childPrefix + child_prefix(false), true);

  Console::log(childPrefix, connector(true), "Value:");
  if (var->value) {
    print_node(var->value, childPrefix + child_prefix(true), true);
  } else {
    Console::log(childPrefix + child_prefix(true), connector(true), "<null>");
  }
}

} // namespace debug::node
