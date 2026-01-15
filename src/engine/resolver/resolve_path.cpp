#include "core/module/scope.hpp"
#include "engine/resolver/Resolver.hpp"

#include "core/module/scope.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_path(parser::node::statement::PathExprNode *path) {
  if (!path) return;

  // Resolve o base primeiro
  resolve(path->base);


  

  // Se o base for um identificador
  if (auto *id = dynamic_cast<core::node::IdentifierNode *>(path->base)) {
    SymbolId base_sym_id = current_scope->resolve_symbol(id->name);

    if (base_sym_id == INVALID_SYMBOL_ID) {
      report_error(DiagnosticCode::UndeclaredSymbol, id->slice);
      return;
    }

    Symbol *base_sym = unit.symbols.get(base_sym_id);

    if (base_sym->kind != SymbolKind::Module) {
      report_error(DiagnosticCode::NotCallable, id->slice);
      return;
    }

    // Se o field for um identificador, resolve dentro do módulo
    if (auto *field_id = dynamic_cast<core::node::IdentifierNode *>(path->field)) {
      core::Scope *module_scope = current_scope->resolve_import(id->name);

      if (!module_scope) {
        report_error(DiagnosticCode::UndeclaredSymbol, id->slice);
        return;
      }

      SymbolId field_sym = module_scope->resolve_symbol(field_id->name);

      if (field_sym == INVALID_SYMBOL_ID) {
        report_error(DiagnosticCode::UndeclaredSymbol, field_id->slice);
        return;
      }

      path->symbol_id = field_sym;
    }
  }
}
