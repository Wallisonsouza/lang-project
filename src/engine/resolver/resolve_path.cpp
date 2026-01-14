#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_path(parser::node::statement::PathExprNode *path) {
  // if (!path || path->segments.empty()) return;

  // core::Scope *scope = current_scope;

  // for (size_t i = 0; i + 1 < path->segments.size(); ++i) {
  //   const std::string &name = path->segments[i]->name;

  //   scope = scope->resolve_import(name);

  //   if (!scope) {
  //     std::cout << "[resolve_path] Prefix not found: " << name << "\n";
  //     return;
  //   }
  // }

  // const std::string &last = path->segments.back()->name;
  // SymbolId sym = scope->resolve_symbol(last);

  // if (sym == INVALID_SYMBOL_ID) {
  //   std::cout << "[resolve_path] Symbol not found: " << last << "\n";
  //   return;
  // }

  // path->symbol_id = sym;
}
