#include "Resolver.hpp"
#include "core/AST.hpp"
#include "core/node/NodeKind.hpp"

#include "engine/parser/node/literal_nodes.hpp"
#include "engine/resolver/resolve_identifier.hpp"
#include "resolve_type.hpp"
#include "resolve_variable_declaration.hpp"
#include "resolver_function_call.hpp"

namespace resolver {

void Resolver::resolve(core::node::Node *node) {
  if (!node) return;

  switch (node->kind) {

  // case core::node::NodeKind::VariableDeclaration:
  //   resolve_variable_declaration(
  //       *this, static_cast<node::VariableDeclarationNode *>(node));
  //   break;
  case core::node::NodeKind::Identifier: resolve_identifier(*this, static_cast<parser::node::IdentifierNode *>(node)); break;
  // case core::node::NodeKind::Type:
  //   resolve_type(*this, static_cast<core::node::TypeNode *>(node));

  // case core::node::NodeKind::FunctionCall:
  //   resolve_function_call(*this, static_cast<node::FunctionCallNode
  //   *>(node)); break;
  default: break;
  }
}

void Resolver::resolve_ast(AST &ast) {
  for (auto &node : ast.get_nodes()) { resolve(node); }
}

void Resolver::report_error(DiagnosticCode code, Slice slice) {
  if (diag_target) {
    // diag_target->report_error(code, slice);
  }
}

} // namespace resolver
