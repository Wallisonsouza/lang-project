#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_import_node(parser::node::statement::ImportNode *node) {

  std::vector<std::string> path_segments;
  for (auto *id : node->path) { path_segments.push_back(id->name); }

  auto &modules = unit.context.modules;

  core::ModuleId module_id = modules.find_path(path_segments);
  core::Module *module = modules.get(module_id);

  if (module_id == core::INVALID_MODULE || !module) {
    // unit.diagnostics.emit({DiagnosticCode::ModuleNotFound, node->slice});
    return;
  }

  Resolver module_resolver(unit, &module->module_scope);

  for (auto &mod_node : module->ast.get_nodes()) { module_resolver.resolve(mod_node); }

  current_scope->import_scope(module->name, &module->module_scope);
}
