#pragma once
#include "symbol.hpp"
#include <cstdint>
#include <unordered_map>
#include <vector>

struct SymbolManager {
  std::vector<Symbol> symbols;
  std::unordered_map<std::string, SymbolId> name_to_id;

  SymbolId create_symbol(const std::string &name, SymbolKind kind,
                         Visibility visibility = Visibility::Private,
                         bool is_builtin = false,
                         core::node::Node *decl = nullptr) {
    SymbolId id = symbols.size();
    symbols.emplace_back(name, kind, visibility, is_builtin, decl);
    name_to_id[name] = id;
    return id;
  }

  SymbolId find(const std::string &name) const {
    auto it = name_to_id.find(name);
    return it != name_to_id.end() ? it->second : SIZE_MAX;
  }

  Symbol *get(SymbolId id) { return &symbols[id]; }
};
