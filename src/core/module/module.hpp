#pragma once
#include "core/module/scope.hpp"
#include "core/node/Node.hpp"
#include <string>
#include <unordered_map>

namespace core {

struct Module {
  std::string name;

  Scope module_scope;
  Module *parent = nullptr;
  std::unordered_map<std::string, Module *> children;

  Module(std::string name, Module *parent_module = nullptr)
      : name(std::move(name)), module_scope(nullptr), parent(parent_module) {}

  core::node::Node *find(const std::string &name) {
    auto sym = module_scope.find(name);
    if (!sym || sym->visibility != core::Visibility::Public)
      return nullptr;
    return sym->declaration;
  }

  void add_child(Module *child) {
    if (child) {
      children[child->name] = child;
      child->parent = this;
    }
  }

  std::string full_name() const {
    if (!parent)
      return name;
    return parent->full_name() + "." + name;
  }
};

} // namespace core
