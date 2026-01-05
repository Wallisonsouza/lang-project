#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/resolver/Resolver.hpp"

inline void resolve_native_function_declaration(CompilationUnit &unit, resolver::Resolver &resolver, core::node::NativeFunctionDeclarationNode *node) {

  SymbolId id = unit.symbols.create_symbol(node->name, SymbolKind::Function, Visibility::Public, true, node);
  auto symbol = unit.symbols.get(id);
  resolver.current_scope->add_symbol(node->name, id);

  node->symbol_id = id;
  symbol->declaration = node;
}
