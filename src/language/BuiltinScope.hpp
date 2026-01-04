#pragma once
#include "core/module/scope.hpp"
#include "core/node/Type.hpp"
#include <string>

namespace ayla {

inline void make_ayla_std(core::Scope &scope) {
  // auto add_type = [&](std::string name) {
  //   auto *type_node =
  //   scope.arena.create<core::node::TypeDeclarationNode>(name,
  //   std::vector<std::string>{}); scope.declare(name, core::SymbolKind::Type,
  //   type_node, core::Visibility::Public, true);
  // };

  // auto add_generic = [&](std::string name, std::initializer_list<std::string>
  // params) {
  //   auto *type_node =
  //   scope.arena.create<core::node::TypeDeclarationNode>(name,
  //   std::vector<std::string>(params.begin(), params.end()));
  //   scope.declare(name, core::SymbolKind::Type, type_node,
  //   core::Visibility::Public, true);
  // };

  // // Tipos primitivos
  // add_type("Number");
  // add_type("String");
  // add_type("Bool");
  // add_type("Void");

  // // Genéricos
  // add_generic("Option", {"T"});
  // add_generic("Result", {"T", "E"});
  // add_generic("Array", {"T"});
}

} // namespace ayla
