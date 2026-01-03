#include "Resolver.hpp"
#include "core/AST.hpp"
#include "core/node/NodeKind.hpp"

#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"

#include "engine/resolver/resolve_binary_expression.hpp"
#include "engine/resolver/resolve_identifier.hpp"
#include "engine/resolver/resolve_import_node.hpp"
#include "engine/resolver/resolve_path.hpp"
#include "engine/resolver/resolve_type.hpp"
#include "engine/resolver/resolve_variable_declaration.hpp"
#include "engine/resolver/resolver_function_call.hpp"

namespace resolver {

void Resolver::resolve(CompilationUnit &unit, core::node::Node *node) {

  if (!node)
    return;

  switch (node->kind) {

  case core::node::NodeKind::BinaryExpression:
    resolve_binary_expression(
        unit, *this, static_cast<parser::node::BinaryExpressionNode *>(node));
    break;

  case core::node::NodeKind::PathExpr:
    resolve_path(unit, *this,
                 static_cast<parser::node::statement::PathExprNode *>(node));
    break;

  case core::node::NodeKind::Import:
    resolve_import_node(
        unit, *this, static_cast<parser::node::statement::ImportNode *>(node));
    break;

  case core::node::NodeKind::Identifier:
    resolve_identifier_node(unit, *this,
                            static_cast<parser::node::IdentifierNode *>(node));
    break;

  case core::node::NodeKind::FunctionCall:
    resolve_function_call(unit, *this,
                          static_cast<parser::node::FunctionCallNode *>(node));
    break;

  default:
    break;
  }
}

void Resolver::resolve_ast(CompilationUnit &unit) {
  for (auto *node : unit.ast.get_nodes()) {
    resolve(unit, node);
  }
}

void Resolver::report_error(DiagnosticCode code, Slice slice) {
  if (diag_target) {
  }
}

} // namespace resolver
