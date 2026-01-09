#include "Resolver.hpp"
#include "core/node/Type.hpp"

void Resolver::resolve_function_call(parser::node::FunctionCallNode *node) {

  if (!node) return;

  // resolve o callee e os argumentos primeiro
  resolve(node->callee);

  for (auto *arg : node->args) { resolve(arg); }

  if (node->callee->kind != core::node::NodeKind::Identifier) {
    // report_error(DiagnosticCode::NotCallable, node->callee->slice);
    return;
  }

  auto *id_node = static_cast<core::node::IdentifierNode *>(node->callee);

  // Agora find retorna SymbolId
  SymbolId sym_id = current_scope->resolve_symbol(id_node->name);

  if (sym_id == SIZE_MAX) {
    // report_error(DiagnosticCode::UndeclaredIdentifier, id_node->slice);
    return;
  }

  Symbol *sym = unit.symbols.get(sym_id);

  if (sym->kind != SymbolKind::Function) {
    // report_error(DiagnosticCode::NotCallable, id_node->slice);
    return;
  }

  node->symbol_id = sym_id;
}
