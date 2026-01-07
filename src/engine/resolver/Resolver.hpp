#pragma once
#include "core/module/scope.hpp"
#include "core/node/Node.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"

namespace resolver {

struct Resolver {

  core::Scope *current_scope;

  explicit Resolver(core::Scope *global) : current_scope(global) {}

  void resolve(CompilationUnit &unit, core::node::Node *node);
  void resolve_ast(CompilationUnit &unit);
  void push_scope();
  void pop_scope();
};

} // namespace resolver
