#pragma once
#include "Resolver.hpp"
#include "core/memory/symbol.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"

inline void resolve_variable_declaration(CompilationUnit &unit, resolver::Resolver &resolver, parser::node::VariableDeclarationNode *var) {

  if (resolver.current_scope->has_symbol_local(var->name)) { return; }

  if (var->type) { resolver.resolve(unit, var->type); }

  if (var->value) { resolver.resolve(unit, var->value); }

  auto symbol_id = unit.symbols.create_symbol(var->name, SymbolKind::Variable);

  resolver.current_scope->add_symbol(var->name, symbol_id);

  var->symbol_id = symbol_id;
}
