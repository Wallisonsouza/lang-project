#include "Resolver.hpp"

void Resolver::resolve_variable_declaration(parser::node::VariableDeclarationNode *node) {

  if (current_scope->has_symbol_local(node->name)) { return; }

  if (node->type) { resolve(node->type); }

  if (node->value) { resolve(node->value); }

  auto symbol_id = unit.symbols.create_symbol(node->name, SymbolKind::Variable);

  current_scope->add_symbol(node->name, symbol_id);

  node->symbol_id = symbol_id;
}
