#pragma once
#include "core/memory/Arena.hpp"
#include "core/node/Node.hpp"
#include <string>
#include <unordered_map>

namespace core {

enum class Visibility { Private, Public };

enum class SymbolKind {
  Type,
  Function,
  Variable,
};

struct Symbol {
  std::u32string name;
  SymbolKind kind;
  node::Node *declaration;
  Visibility visibility;
  bool is_builtin;

  Symbol(std::u32string name, SymbolKind kind, node::Node *declaration, Visibility visibility = Visibility::Private, bool is_builtin = false)
      : name(std::move(name)), kind(kind), declaration(declaration), visibility(visibility), is_builtin(is_builtin) {}
};

struct SymbolManager {
  memory::Arena arena;
  std::unordered_map<std::u32string, Symbol *> symbols;

  Symbol *create_symbol(const std::u32string &name, SymbolKind kind, node::Node *declaration, Visibility visibility = Visibility::Private, bool is_builtin = false) {
    Symbol *sym = arena.create<Symbol>(name, kind, declaration, visibility, is_builtin);
    symbols[name] = sym;
    return sym;
  }

  Symbol *find(const std::u32string &name) {
    auto it = symbols.find(name);
    return it != symbols.end() ? it->second : nullptr;
  }
};
} // namespace core