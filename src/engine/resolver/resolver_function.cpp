#include "Resolver.hpp"
#include "core/node/Type.hpp"
#include "engine/parser/node/statement_nodes.hpp"

void Resolver::resolve_function_declaration(parser::node::FunctionDeclarationNode *node) {

  current_scope->add_symbol(node->identifier->name, node->symbol_id);

  push_scope();

  for (auto *param : node->params) { current_scope->add_symbol(param->identifier->name, param->symbol_id); }

  resolve_block(node->body, false);

  pop_scope();
}

void Resolver::resolve_function_call(parser::node::FunctionCallNode *node) {

  resolve(node->callee);

  for (auto *arg : node->args) { resolve(arg); }

  if (node->callee->kind != core::node::NodeKind::Identifier) {
    // report_error(DiagnosticCode::NotCallable, node->callee->slice);
    return;
  }

  auto *id_node = static_cast<core::node::IdentifierNode *>(node->callee);

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
