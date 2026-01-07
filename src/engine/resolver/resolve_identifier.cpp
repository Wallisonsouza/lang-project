#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_identifier(parser::node::IdentifierNode *node) {
  SymbolId id = current_scope->find(node->name);
  if (id == INVALID_SYMBOL_ID) {
    // unit.diagnostics.emit({DiagnosticCode::UndeclaredSymbol, node->slice},
    //                       unit);

    std::cerr << "Erro simbolo nao econtrado";
    return;
  }
  node->symbol_id = id;
}
