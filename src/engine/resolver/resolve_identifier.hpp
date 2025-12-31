#pragma once

#include "Resolver.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "engine/parser/node/literal_nodes.hpp"

namespace resolver {

inline void resolve_identifier(Resolver &resolver,
                               parser::node::IdentifierNode *id_node) {

  auto *sym = resolver.current_scope->find(id_node->name);

  if (!sym) {
    resolver.report_error(DiagnosticCode::UndeclaredSymbol, id_node->slice);
    return;
  }

  id_node->symbol = sym;
}

} // namespace resolver
