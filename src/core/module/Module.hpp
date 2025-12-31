#pragma once

#include "core/module/Scope.hpp"
#include <string>

namespace core {

struct Module {
  std::u32string name;
  Scope module_scope;

  Module(std::u32string name, std::u32string full, Scope *parent_scope)
      : name(std::move(name)), module_scope(parent_scope) {}

  node::Node *find_public_type(const std::u32string &name) {
    auto sym = module_scope.find(name);

    if (!sym || sym->visibility != Visibility::Public) {
      return nullptr;
    }
    return sym->declaration;
  }
};
} // namespace core