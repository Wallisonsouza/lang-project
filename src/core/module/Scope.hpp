#pragma once

#include "core/node/Node.hpp"
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace core {

enum class Visibility { Private, Public };

template <typename T> struct ScopedSymbol {
  T *node;
  Visibility visibility;
};

struct Scope {
  Scope *parent;

  std::unordered_map<std::u32string, ScopedSymbol<node::Node>> variables;
  std::unordered_map<std::u32string, ScopedSymbol<node::Node>> types;
  std::unordered_map<std::u32string, ScopedSymbol<node::Node>> functions;

  explicit Scope(Scope *parent_scope) : parent(parent_scope) {}

  node::Node *find_variable(const std::u32string &name) {
    Scope *current = this;
    while (current) {
      auto it = current->variables.find(name);
      if (it != current->variables.end()) return it->second.node;
      current = current->parent;
    }
    return nullptr;
  }

  node::Node *find_type(const std::u32string &name) {
    Scope *current = this;
    while (current) {
      auto it = current->types.find(name);
      if (it != current->types.end()) return it->second.node;
      current = current->parent;
    }
    return nullptr;
  }

  node::Node *find_function(const std::u32string &name) {
    Scope *current = this;
    while (current) {
      auto it = current->functions.find(name);
      if (it != current->functions.end()) return it->second.node;
      current = current->parent;
    }
    return nullptr;
  }

  bool has_variable_in_current_scope(const std::u32string &name) const { return variables.contains(name); }

  bool has_function_in_current_scope(const std::u32string &name) const { return functions.contains(name); }

  bool has_type_in_current_scope(const std::u32string &name) const { return types.contains(name); }

  bool has_name_in_current_scope(const std::u32string &name) const { return has_variable_in_current_scope(name) || has_function_in_current_scope(name) || has_type_in_current_scope(name); }

  void add_variable(const std::u32string &name, node::Node *node, Visibility vis = Visibility::Private) {
    if (has_name_in_current_scope(name)) { throw std::runtime_error("Name already declared in this scope"); }
    variables[name] = {node, vis};
  }

  void add_function(const std::u32string &name, node::Node *func, Visibility vis = Visibility::Private) {
    if (has_name_in_current_scope(name)) { throw std::runtime_error("Name already declared in this scope"); }
    functions[name] = {func, vis};
  }

  void add_type(const std::u32string &name, node::Node *type, Visibility vis = Visibility::Private) {
    if (has_name_in_current_scope(name)) { throw std::runtime_error("Name already declared in this scope"); }
    types[name] = {type, vis};
  }
};

} // namespace core
