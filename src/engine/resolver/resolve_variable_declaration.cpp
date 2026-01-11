#include "Resolver.hpp"

void Resolver::resolve_variable_declaration(parser::node::VariableDeclarationNode *node) {

  if (current_scope->has_symbol_local(node->identifier->name)) {

    report_error(DiagnosticCode::RedeclaredIdentifier, node->identifier->slice, {{"name", node->identifier->name}});

    return;
  }

  auto symbol_id = unit.symbols.create_symbol(node->identifier->name, SymbolKind::Variable);
  current_scope->add_symbol(node->identifier->name, symbol_id);
  node->symbol_id = symbol_id;

  if (node->type) resolve(node->type);
  if (node->value) resolve(node->value);
}
