#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_import_node(parser::node::statement::ImportNode *node) {
  std::vector<std::string> path_segments;

  for (auto *id : node->path) path_segments.push_back(id->name);

  auto &modules = unit.context.modules;

  core::ModuleId module_id = modules.find_path(path_segments);
  core::Module *module = modules.get(module_id);

  if (module_id == core::INVALID_MODULE || !module) { return; }

  // Resolver temporário para o módulo importado
  Resolver module_resolver(unit, &module->module_scope);

  // Resolve todos os nós do módulo **usando o escopo do módulo**
  for (auto &mod_node : module->ast.get_nodes()) { module_resolver.resolve(mod_node); }

  // Faz o módulo importado estar disponível no escopo atual

  auto symbol_id = unit.symbols.create_symbol(module->name, SymbolKind::Module, Visibility::Public, true, node);

  current_scope->add_symbol(module->name, symbol_id);

  if (current_scope) { current_scope->import_scope(module->name, &module->module_scope); }
}
