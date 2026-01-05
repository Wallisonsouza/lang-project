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

  explicit Scope(Scope *parent_scope) : parent(parent_scope) {}

  SymbolId find(const std::string &name) const {

    std::cout << "[Scope::find] Searching for '" << name << "' in current scope\n";

    // 1️⃣ verifica símbolos locais
    auto it = symbols.find(name);
    if (it != symbols.end()) {
      std::cout << "[Scope::find] Found symbol '" << name << "' locally\n";
      return it->second;
    }

    // 2️⃣ verifica escopos importados
    for (auto &[alias, scope] : imports) {
      std::cout << "[Scope::find] Checking import '" << alias << "' for '" << name << "'\n";
      SymbolId id = scope->find(name);
      if (id != SIZE_MAX) {
        std::cout << "[Scope::find] Found symbol '" << name << "' in import '" << alias << "'\n";
        return id;
      }
    }

    // 3️⃣ sobe para o parent
    if (parent) {
      std::cout << "[Scope::find] Going up to parent scope for '" << name << "'\n";
      return parent->find(name);
    }

    // não encontrado
    std::cout << "[Scope::find] Symbol '" << name << "' not found anywhere\n";
    return SIZE_MAX;
  }

  SymbolId add_symbol(const std::string &name, SymbolId id) {
    auto it = symbols.find(name);
    if (it != symbols.end()) {
      std::cout << "[Scope::add_symbol] Symbol '" << name << "' already exists, returning existing id\n";
      return it->second;
    }
    std::cout << "[Scope::add_symbol] Adding symbol '" << name << "' with id " << id << "\n";
    symbols[name] = id;
    return id;
  }

  void import_scope(const std::string &alias, Scope *scope) {
    std::cout << "[Scope::import_scope] Importing scope '" << alias << "'\n";
    imports[alias] = scope;
  }
};

} // namespace core
