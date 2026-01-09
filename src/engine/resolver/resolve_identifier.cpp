#include "core/node/Type.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_identifier(core::node::IdentifierNode *node) {

  SymbolId id = current_scope->resolve_symbol(node->name);

  if (id == INVALID_SYMBOL_ID) {
    // unit.diagnostics.emit({DiagnosticCode::UndeclaredSymbol, node->slice},
    //                       unit);

   
    return;
  }
  node->symbol_id = id;
}
