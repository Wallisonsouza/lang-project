#pragma once

#include "core/memory/symbol.hpp"
#include "core/module/scope.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/resolver/Resolver.hpp"
#include <iostream>

namespace resolver {

inline SymbolId resolve_path(CompilationUnit &unit, Resolver &resolver, parser::node::statement::PathExprNode *path) {

  core::Scope *current_scope = resolver.current_scope;
  SymbolId sym = INVALID_SYMBOL_ID;

  std::cout << "[resolve_path] Resolving path: ";
  for (const auto &s : path->segments) std::cout << s->name << "::";
  std::cout << "\n";

  for (size_t i = 0; i < path->segments.size(); ++i) {
    auto *seg = path->segments[i];
    std::cout << "[resolve_path] Segment: " << seg->name << "\n";

    if (i == path->segments.size() - 1) {
      sym = current_scope->find(seg->name);
      if (sym != INVALID_SYMBOL_ID) {
        std::cout << "[resolve_path] Found symbol '" << seg->name << "'\n";
      } else {
        std::cout << "[resolve_path] Symbol '" << seg->name << "' not founda!\n";
        // Aqui você pode emitir um erro no CompilationUnit
        unit.diagnostics.emit({DiagnosticCode::UndeclaredSymbol, seg->slice}, unit);
      }
    } else {
      auto it = current_scope->imports.find(seg->name);
      if (it == current_scope->imports.end()) {
        std::cout << "[resolve_path] Module '" << seg->name << "' not found!\n";
        return INVALID_SYMBOL_ID;
      }
      std::cout << "[resolve_path] Found module '" << seg->name << "'\n";
      current_scope = it->second;
    }
  }

  if (sym == INVALID_SYMBOL_ID) { std::cout << "invalid"; }

  path->symbol_id = sym;
  return sym;
}

} // namespace resolver
