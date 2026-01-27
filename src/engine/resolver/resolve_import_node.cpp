#include "diagnostic/diagnostic_code.hpp"
#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_import_node(parser::node::statement::ImportNode *node) {

  auto &module_manager = unit.context.modules;

  size_t failed_index;
  
  auto id = module_manager.find_path(node->path, failed_index);

  if (id == SIZE_MAX) {

    auto segment = node->path[failed_index];

    report_error(DiagnosticCode::ModuleNotFound, segment->slice);

    return;
  }

  core::Module *module = module_manager.get(id);

  // Resolver temporário para o módulo importado
  Resolver module_resolver(unit, &module->module_scope);

  // Resolve todos os nós do módulo **usando o escopo do módulo**
  for (auto &mod_node : module->ast.get_nodes()) {
    module_resolver.resolve(mod_node);
  }

  // Faz o módulo importado estar disponível no escopo atual

  auto symbol_id = unit.symbols.create_symbol(module->name, SymbolKind::Module,
                                              Visibility::Public, true, node);

  current_scope->add_symbol(module->name, symbol_id);

  if (current_scope) {
    current_scope->import_scope(module->name, &module->module_scope);
  }
}
