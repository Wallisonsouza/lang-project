#pragma once

#include "core/memory/symbol.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>

namespace core {

struct Scope {

  Scope *parent;

  std::unordered_map<std::string, Scope *> imports;
  std::unordered_map<std::string, SymbolId> symbols;

  Scope(Scope *parent_scope) : parent(parent_scope) {}

  SymbolId resolve_symbol(const std::string &name) const {
    auto it = symbols.find(name);
    if (it != symbols.end()) return it->second;

    if (parent) return parent->resolve_symbol(name);

    return INVALID_SYMBOL_ID;
  }

  Scope *resolve_import(const std::string &alias) const {
    auto it = imports.find(alias);
    if (it != imports.end()) return it->second;

    if (parent) return parent->resolve_import(alias);

    return nullptr;
  }

  SymbolId add_symbol(const std::string &name, SymbolId id) {
    auto it = symbols.find(name);
    if (it != symbols.end()) return it->second;
    symbols[name] = id;
    return id;
  }

  bool has_symbol_local(const std::string &name) const { return symbols.find(name) != symbols.end(); }

  void import_scope(const std::string &alias, Scope *scope) { imports[alias] = scope; }
};

} // namespace core
