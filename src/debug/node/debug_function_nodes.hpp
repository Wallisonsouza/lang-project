#pragma once
#include "core/node/Node.hpp"
#include "debug/console/console.hpp"
#include "debug/node/debug_node_helpers.hpp"
#include "debug_common.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "utils/Utf8.hpp"
#include <iostream>
#include <string>

namespace debug::node {

inline void print_variable(parser::node::FunctionDeclarationNode *node,
                           const std::string &prefix = "", bool isLast = true) {
  if (!node)
    return;

  std::cout << "pass";

  auto *func = static_cast<parser::node::FunctionDeclarationNode *>(node);

  // Log do nó principal
  Console::log(prefix, connector(isLast),
               "FunctionDeclaration: ", utils::Utf::utf32to8(func->name));

  std::string childPrefix = prefix + child_prefix(isLast);

  // Parâmetros
  for (size_t i = 0; i < func->params.size(); ++i) {
    bool lastParam = (i == func->params.size() - 1);
    Console::log(childPrefix, connector(lastParam),
                 "Param: ", utils::Utf::utf32to8(func->params[i]->name));
    // Tipo do parâmetro
    print_node(func->params[i]->type, childPrefix + child_prefix(lastParam),
               true);
  }

  // Tipo de retorno
  if (func->return_type) {
    Console::log(childPrefix, connector(true), "ReturnType:");
    print_node(func->return_type, childPrefix + child_prefix(true), true);
  }

  // // Corpo da função
  // if (func->body) {
  //   Console::log(childPrefix, connector(true), "Body:");
  //   print_node_list(func->body->statements, childPrefix +
  //   child_prefix(true));
  // }
}

} // namespace debug::node
