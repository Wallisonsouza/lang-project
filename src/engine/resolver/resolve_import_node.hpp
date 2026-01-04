#pragma once

#include "Resolver.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

namespace resolver {

inline void resolve_import_node(CompilationUnit &unit, Resolver &resolver,
                                parser::node::statement::ImportNode *node) {

  std::vector<std::string> path_segments;
  for (auto *id : node->path) {
    path_segments.push_back(id->name);
  }

  core::ModuleId module_id = unit.modules.find_path(path_segments);

  if (module_id == SIZE_MAX) {
    unit.diagnostics.emit({DiagnosticCode::ModuleNotFound, node->slice}, unit);
    return;
  }

  core::Module *module = unit.modules.get(module_id);

  resolver.current_scope->import_scope(module->name, &module->module_scope);
}

} // namespace resolver
