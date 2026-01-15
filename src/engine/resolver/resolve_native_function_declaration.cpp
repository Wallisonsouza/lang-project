#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_native_function_declaration(core::node::NativeFunctionDeclarationNode *node) {

  SymbolId id = unit.symbols.create_symbol(node->identifier->name, SymbolKind::Function, Visibility::Public, true, node);

  auto symbol = unit.symbols.get(id);
  current_scope->add_symbol(node->identifier->name, id);

  node->symbol_id = id;
  symbol->declaration = node;
}
