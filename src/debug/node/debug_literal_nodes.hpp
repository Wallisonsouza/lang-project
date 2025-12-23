#pragma once
#include "core/node/Node.hpp"
#include "debug/console/console.hpp"
#include "debug/node/debug_node_helpers.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "utils/Utf8.hpp"
#include <string>

namespace debug::node {

inline void print_literal_node(core::node::Node *node,
                               const std::string &prefix, bool isLast) {
  switch (node->kind) {
  case core::node::NodeKind::NumberLiteral: {
    auto *num = static_cast<parser::node::NumberLiteralNode *>(node);
    Console::log(prefix, connector(isLast),
                 "NumberLiteral: ", std::to_string(num->value));
    break;
  }
  case core::node::NodeKind::StringLiteral: {
    auto *str = static_cast<parser::node::StringLiteralNode *>(node);
    Console::log(prefix, connector(isLast),
                 "StringLiteral: ", utils::Utf::utf32to8(str->value));
    break;
  }
  default:
    break;
  }
}

} // namespace debug::node
