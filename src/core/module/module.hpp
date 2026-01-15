#pragma once
#include "core/AST.hpp"
#include "core/module/scope.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace core {

using ModuleId = size_t;

inline constexpr ModuleId INVALID_MODULE = SIZE_MAX;

struct Module {

  std::string name;
  Scope module_scope;
  AST ast;

  ModuleId parent = SIZE_MAX;
  std::unordered_map<std::string, ModuleId> children;

  explicit Module(std::string n, ModuleId p = SIZE_MAX) : name(std::move(n)), parent(p), module_scope(nullptr) {}

  SymbolId find_symbol(const std::string &name) {
    SymbolId id = module_scope.resolve_symbol(name);
    return id;
  }

  void add_child(const std::string &child_name, ModuleId child_id) { children[child_name] = child_id; }

  std::string full_name(const std::vector<Module> &all_modules) const {
    if (parent == SIZE_MAX) return name;
    return all_modules[parent].full_name(all_modules) + "." + name;
  }
};

} // namespace core
