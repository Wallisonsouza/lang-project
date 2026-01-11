#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_identifier(core::node::IdentifierNode *node) {
  if (!node) return;

  SymbolId id = current_scope->resolve_symbol(node->name);

  if (id == INVALID_SYMBOL_ID) {

    auto *diag = unit.diagns.create(DiagnosticCode::UndeclaredSymbol, node->slice);

    diag->set_expected("identificador declarado");
    diag->set_found(node->name);

    return;
  }

  node->symbol_id = id;
}
