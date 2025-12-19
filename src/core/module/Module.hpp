#pragma once
#include "core/module/Scope.hpp"
#include "core/node/Node.hpp"
#include <string>
#include <unordered_map>

namespace core {
struct Module {
  std::u32string name;
  std::u32string full_name;

  Scope module_scope;
  Module *parent = nullptr;

  std::unordered_map<std::u32string, Module *> children;

  Module(std::u32string name, std::u32string full, Scope *parent_scope) : name(std::move(name)), full_name(std::move(full)), module_scope(parent_scope) {}

  node::Node *find_public_type(const std::u32string &name) {
    auto it = module_scope.types.find(name);
    if (it == module_scope.types.end()) return nullptr;
    if (it->second.visibility != Visibility::Public) return nullptr;
    return it->second.node;
  }

  node::Node *find_public_function(const std::u32string &name) {
    auto it = module_scope.functions.find(name);
    if (it == module_scope.functions.end()) return nullptr;
    if (it->second.visibility != Visibility::Public) return nullptr;
    return it->second.node;
  }
};
} // namespace core