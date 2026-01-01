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
  std::unordered_map<std::u32string, Scope *> imports;

  explicit Scope(Scope *parent_scope);

  Symbol *declare(const std::u32string &name, SymbolKind kind, node::Node *declaration, Visibility visibility = Visibility::Private, bool is_builtin = false);

  Symbol *find(const std::u32string &name);

  void import_scope(const std::u32string &alias, Scope *scope);
};

} // namespace core
