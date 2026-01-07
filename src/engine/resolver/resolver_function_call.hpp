#include "Resolver.hpp"
#include "core/node/NodeKind.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement_nodes.hpp"

namespace resolver {

inline void resolve_function_call(CompilationUnit &unit, Resolver &resolver, parser::node::FunctionCallNode *node) {

  if (!node) return;

  // resolve o callee e os argumentos primeiro
  resolver.resolve(unit, node->callee);

  for (auto *arg : node->args) { resolver.resolve(unit, arg); }

  if (node->callee->kind != core::node::NodeKind::Identifier) {
    // resolver.report_error(DiagnosticCode::NotCallable, node->callee->slice);
    return;
  }

  auto *id_node = static_cast<parser::node::IdentifierNode *>(node->callee);

  // Agora find retorna SymbolId
  SymbolId sym_id = resolver.current_scope->find(id_node->name);

  if (sym_id == SIZE_MAX) {
    // resolver.report_error(DiagnosticCode::UndeclaredIdentifier, id_node->slice);
    return;
  }

  Symbol *sym = unit.symbols.get(sym_id);

  if (sym->kind != SymbolKind::Function) {
    // resolver.report_error(DiagnosticCode::NotCallable, id_node->slice);
    return;
  }

  node->symbol_id = sym_id;
}

} // namespace resolver
