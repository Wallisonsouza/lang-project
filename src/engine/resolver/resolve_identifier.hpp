#pragma once

#include "Resolver.hpp"
#include "core/memory/symbol.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include <iostream>

namespace resolver {

inline void resolve_identifier_node(CompilationUnit &unit, Resolver &resolver, parser::node::IdentifierNode *node) {
  SymbolId id = resolver.current_scope->find(node->name);
  if (id == INVALID_SYMBOL_ID) {
    // unit.diagnostics.emit({DiagnosticCode::UndeclaredSymbol, node->slice},
    //                       unit);

    std::cerr << "Erro simbolo nao econtrado";
    return;
  }
  node->symbol_id = id;
}

} // namespace resolver
