// resolver/Resolver.hpp
#pragma once
#include "core/AST.hpp"
#include "core/module/scope.hpp"
#include "core/node/Node.hpp"
#include "core/token/Location.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/CompilationUnit.hpp"

namespace resolver {

struct Resolver {

  core::Scope *current_scope;
  DiagnosticEngine *diag_target;

  explicit Resolver(core::Scope *global) : current_scope(global) {}

  void resolve(CompilationUnit &unit, core::node::Node *node);
  void resolve_ast(CompilationUnit &unit);
  void push_scope();
  void pop_scope();

  void report_error(DiagnosticCode code, Slice slice);
};

} // namespace resolver
