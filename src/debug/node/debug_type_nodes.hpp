#pragma once

#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "debug/console/console.hpp"
#include "debug/node/debug_node_helpers.hpp"
#include "utils/Utf8.hpp"
#include <string>

namespace debug::node {

inline void print_type_node(core::node::Node *node, const std::string &prefix,
                            bool isLast) {
  switch (node->kind) {
  case core::node::NodeKind::TypeDeclaration: {
    auto *td = static_cast<core::node::TypeDeclarationNode *>(node);
    Console::log(prefix, connector(isLast),
                 "TypeDeclaration: ", utils::Utf::utf32to8(td->name));
    for (size_t i = 0; i < td->type_params.size(); i++) {
      Console::log(prefix + child_prefix(isLast),
                   "Param: ", utils::Utf::utf32to8(td->type_params[i]));
    }
    break;
  }
  case core::node::NodeKind::Type: {
    auto *type = static_cast<core::node::TypeNode *>(node);
    Console::log(prefix, connector(isLast),
                 "Type: ", utils::Utf::utf32to8(type->name));
    break;
  }
  default:
    break;
  }
}

} // namespace debug::node
