#pragma once
#include "Resolver.hpp"
#include "core/memory/symbol.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <iostream>

#define RESOLVER_DEBUG

#ifdef RESOLVER_DEBUG
#define RESOLVE_LOG(msg) std::cerr << "[Resolver] " << msg << "\n"
#else
#define RESOLVE_LOG(msg) ((void)0)
#endif

namespace resolver {

inline void
resolve_variable_declaration(CompilationUnit &unit, Resolver &resolver,
                             parser::node::VariableDeclarationNode *var) {

  RESOLVE_LOG("Resolving variable declaration: " << var->name);

  if (var->value) {
    RESOLVE_LOG("resolving initializer");
    resolver.resolve(unit, var->value);
  }

  if (var->type) {
    RESOLVE_LOG("resolving explicit type");
    resolver.resolve(unit, var->type);
  }

  auto symbol_id = unit.symbols.create_symbol(var->name, SymbolKind::Variable);

  RESOLVE_LOG("created symbol id=" << symbol_id);

  resolver.current_scope->add_symbol(var->name, symbol_id);

  RESOLVE_LOG("added to current scope");

  var->symbol_id = symbol_id;

  RESOLVE_LOG("attached symbol to AST node");
}

} // namespace resolver
