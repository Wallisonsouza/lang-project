#include "scope.hpp"
#include <string>

namespace core {

Scope::Scope(Scope *parent_scope) : parent(parent_scope) {}

core::Symbol *Scope::declare(const std::string &name, core::SymbolKind kind, core::node::Node *declaration, core::Visibility visibility, bool is_builtin) {
  if (symbols.contains(name)) return nullptr;
  core::Symbol *sym = arena.create<core::Symbol>(name, kind, declaration, visibility, is_builtin);
  symbols[name] = sym;
  return sym;
}

core::Symbol *Scope::find(const std::string &name) {

  for (Scope *s = this; s; s = s->parent) {
    auto it = s->symbols.find(name);
    if (it != s->symbols.end()) return it->second;
  }

  return nullptr;
}

void Scope::import_scope(const std::string &alias, Scope *scope) {
  if (!scope) return;
  imports.try_emplace(alias, scope);
}

} // namespace core
