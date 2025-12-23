#pragma once

#include "core/memory/Arena.hpp"
#include "core/module/Symbol.hpp"
#include "core/node/Node.hpp"
#include <string>
#include <unordered_map>

namespace core {

struct Scope {
  Scope *parent;
  core::memory::Arena arena;
  std::unordered_map<std::u32string, Symbol *> symbols;

  explicit Scope(Scope *parent_scope) : parent(parent_scope) {}

  Symbol *declare(const std::u32string &name, SymbolKind kind,
                  node::Node *declaration,
                  Visibility visibility = Visibility::Private,
                  bool is_builtin = false) {
    if (symbols.contains(name))
      return nullptr;

    Symbol *sym =
        arena.create<Symbol>(name, kind, declaration, visibility, is_builtin);

    symbols[name] = sym;
    return sym;
  }

  Symbol *find(const std::u32string &name) {
    for (Scope *s = this; s; s = s->parent) {
      auto it = s->symbols.find(name);
      if (it != s->symbols.end())
        return it->second;
    }
    return nullptr;
  }
};

} // namespace core
