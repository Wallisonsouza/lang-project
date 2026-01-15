#include "Resolver.hpp"

void Resolver::resolve_function_declaration(parser::node::FunctionDeclarationNode *node) {

  push_scope();

  for (auto *param : node->params) {
    if (current_scope->has_symbol_local(param->identifier->name)) {
      report_error(DiagnosticCode::RedeclaredIdentifier, param->identifier->slice, {{"name", param->identifier->name}});
      continue;
    }

    auto symbol = unit.symbols.create_symbol(param->identifier->name, SymbolKind::Variable);
    current_scope->add_symbol(param->identifier->name, symbol);

    param->symbol_id = symbol;
  }

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
