#include "Resolver.hpp"
#include <iostream>

void Resolver::resolve_variable_declaration(parser::node::VariableDeclarationNode *node) {
  if (!node || !node->identifier) return;

  resolve(node->identifier);

  // Emitir erro se redefinição
  if (current_scope->has_symbol_local(node->identifier->name)) {

    std::cout << "aaaaaaaaaaaaaaaaaaa";
    // unit.diagnostics.emit_error("Variable '" + node->identifier->name + "' already declared in this scope");
    return; // ou continue, dependendo de como quer lidar com erro
  }

  if (node->type) resolve(node->type);
  if (node->value) resolve(node->value);

  auto symbol_id = unit.symbols.create_symbol(node->identifier->name, SymbolKind::Variable);
  current_scope->add_symbol(node->identifier->name, symbol_id);
  node->symbol_id = symbol_id;
}
