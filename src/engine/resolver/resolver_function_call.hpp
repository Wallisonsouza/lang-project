#include "Resolver.hpp"
#include "core/module/Symbol.hpp"
#include "core/node/NodeKind.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement_nodes.hpp"

namespace resolver {

inline void resolve_function_call(CompilationUnit &unit, Resolver &resolver, parser::node::FunctionCallNode *node) {

  if (!node) return;

  resolver.resolve(unit, node->callee);

  for (auto *arg : node->args) { resolver.resolve(unit, arg); }

  if (node->callee->kind != core::node::NodeKind::Identifier) {
    resolver.report_error(DiagnosticCode::NotCallable, node->callee->slice);
    return;
  }

  auto *id = static_cast<parser::node::IdentifierNode *>(node->callee);

  core::Symbol *sym = resolver.current_scope->find(id->name);

  if (!sym) {
    resolver.report_error(DiagnosticCode::UndeclaredIdentifier, id->slice);
    return;
  }

  if (sym->kind != core::SymbolKind::Function) {
    resolver.report_error(DiagnosticCode::NotCallable, id->slice);
    return;
  }

  node->symbol = sym;
}

} // namespace resolver
