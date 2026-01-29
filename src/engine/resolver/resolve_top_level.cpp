#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_top_level() {

  for (auto *node : unit.ast.get_nodes()) {

    switch (node->kind) {

    case core::ast::NodeKind::FunctionDeclaration: {
      auto *fn = static_cast<parser::node::FunctionDeclarationNode *>(node);

      if (current_scope->has_symbol_local(fn->identifier->name)) {
        report_error(DiagnosticCode::RedeclaredIdentifier, fn->identifier->slice, {{"name", fn->identifier->name}});
        break;
      }

      auto id = unit.symbols.create_symbol(fn->identifier->name, SymbolKind::Function, Visibility::Public, false, fn);
      fn->symbol_id = id;

      auto symbol = unit.symbols.get(id);
      symbol->declaration = fn;

      current_scope->add_symbol(fn->identifier->name, id);

      break;
    }

    case core::ast::NodeKind::NativeFunctionDeclaration: {
      auto *fn = static_cast<core::ast::NativeFunctionDeclarationNode *>(node);

      auto symbol = unit.symbols.create_symbol(fn->identifier->name, SymbolKind::Function, Visibility::Public, true, fn);
      fn->symbol_id = symbol;
      current_scope->add_symbol(fn->identifier->name, fn->symbol_id);

      break;
    }

    default: break;
    }
  }
}
