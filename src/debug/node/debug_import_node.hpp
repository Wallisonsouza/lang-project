#pragma once
#include "core/node/Node.hpp"
#include "debug/console/console.hpp"
#include "debug/node/debug_node_helpers.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "utils/Utf8.hpp"
#include <string>

namespace debug::node {

inline void print_import_node(core::node::Node *node, const std::string &prefix,
                              bool isLast) {
  if (!node)
    return;

  if (node->kind != core::node::NodeKind::ImportStatement)
    return;

  auto *importNode = static_cast<parser::node::statement::ImportNode *>(node);

  Console::log(prefix, connector(isLast), "ImportStatement: ");

  std::string childPrefix = prefix + child_prefix(isLast);

  for (size_t i = 0; i < importNode->path.size(); ++i) {
    bool last = (i == importNode->path.size() - 1);

    Console::log(childPrefix, connector(last),
                 utils::Utf::utf32to8(importNode->path[i]));
  }
}

} // namespace debug::node
