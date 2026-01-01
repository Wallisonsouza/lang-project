#pragma once

#include "Resolver.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

namespace resolver {

inline void resolve_import_node(CompilationUnit &unit, Resolver &resolver, parser::node::statement::ImportNode *node) {

  auto *module = unit.context.module_manager.find_path(node->path);

  if (!module) {
    unit.diagnostics.emit({DiagnosticCode::ModuleNotFound, node->slice}, unit.source.buffer);
    return;
  }

  resolver.current_scope->import_scope(module->name, &module->module_scope);
}

} // namespace resolver
