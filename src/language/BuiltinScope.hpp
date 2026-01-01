#pragma once
#include "core/module/scope.hpp"
#include "core/node/Type.hpp"

namespace ayla {

inline void make_ayla_std(core::Scope &scope) {
  auto add_type = [&](std::u32string name) {
    auto *type_node = scope.arena.create<core::node::TypeDeclarationNode>(name, std::vector<std::u32string>{});
    scope.declare(name, core::SymbolKind::Type, type_node, core::Visibility::Public, true);
  };

  auto add_generic = [&](std::u32string name, std::initializer_list<std::u32string> params) {
    auto *type_node = scope.arena.create<core::node::TypeDeclarationNode>(name, std::vector<std::u32string>(params.begin(), params.end()));
    scope.declare(name, core::SymbolKind::Type, type_node, core::Visibility::Public, true);
  };

  // Tipos primitivos
  add_type(U"Number");
  add_type(U"String");
  add_type(U"Bool");
  add_type(U"Void");

  // Genéricos
  add_generic(U"Option", {U"T"});
  add_generic(U"Result", {U"T", U"E"});
  add_generic(U"Array", {U"T"});
}

} // namespace ayla
