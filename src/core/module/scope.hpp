#pragma once

#include "core/memory/symbol.hpp"
#include <cstdint>
#include <string>
#include <unordered_map>

namespace core {

struct Scope {
  Scope *parent;

  std::unordered_map<std::string, Scope *> imports;
  std::unordered_map<std::string, SymbolId> symbols;

  explicit Scope(Scope *parent_scope) : parent(parent_scope) {}

  SymbolId find(const std::string &name) const {
    auto it = symbols.find(name);
    if (it != symbols.end())
      return it->second;
    if (parent)
      return parent->find(name);
    return SIZE_MAX;
  }

  SymbolId add_symbol(const std::string &name, SymbolId id) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
      return it->second;
    }
    symbols[name] = id;
    return id;
  }

  void import_scope(const std::string &alias, Scope *scope) {
    imports[alias] = scope;
  }
};

} // namespace core
