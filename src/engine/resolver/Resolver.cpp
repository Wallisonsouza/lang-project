#include "Resolver.hpp"
#include "core/AST.hpp"
#include "core/node/NodeKind.hpp"

#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"

#include "engine/resolver/resolve_binary_expression.hpp"
#include "engine/resolver/resolve_identifier.hpp"
#include "engine/resolver/resolve_if_statement.hpp"
#include "engine/resolver/resolve_import_node.hpp"
#include "engine/resolver/resolve_native_function_declaration.hpp"
#include "engine/resolver/resolve_path.hpp"
#include "engine/resolver/resolve_type.hpp"
#include "engine/resolver/resolve_variable_declaration.hpp"
#include "engine/resolver/resolver_function_call.hpp"
namespace resolver {

void Resolver::resolve(CompilationUnit &unit, core::node::Node *node) {

  if (!node) return;

  switch (node->kind) {

  case core::node::NodeKind::NumberLiteral:
  case core::node::NodeKind::StringLiteral:
  case core::node::NodeKind::BooleanLiteral: return;

  case core::node::NodeKind::IfStatement: resolve_if_statement_node(unit, *this, static_cast<parser::node::IfStatementNode *>(node)); break;
  case core::node::NodeKind::Block: resolve_block_node(unit, *this, static_cast<parser::node::BlockNode *>(node)); break;
  case core::node::NodeKind::BinaryExpression: resolve_binary_expression(unit, *this, static_cast<parser::node::BinaryExpressionNode *>(node)); break;

  case core::node::NodeKind::PathExpression: resolve_path(unit, *this, static_cast<parser::node::statement::PathExprNode *>(node)); break;

  case core::node::NodeKind::Import: resolve_import_node(unit, *this, static_cast<parser::node::statement::ImportNode *>(node)); break;

  case core::node::NodeKind::Identifier: resolve_identifier_node(unit, *this, static_cast<parser::node::IdentifierNode *>(node)); break;

  case core::node::NodeKind::FunctionCall: resolve_function_call(unit, *this, static_cast<parser::node::FunctionCallNode *>(node)); break;

  case core::node::NodeKind::VariableDeclaration: resolve_variable_declaration(unit, *this, static_cast<parser::node::VariableDeclarationNode *>(node)); break;
  case core::node::NodeKind::NativeFunctionDeclaration: resolve_native_function_declaration(unit, *this, static_cast<core::node::NativeFunctionDeclarationNode *>(node)); break;
  case core::node::NodeKind::ExpressionStatement: {
    auto *es = static_cast<core::node::ExpressionStatementNode *>(node);
    resolve(unit, es->expr);
    break;
  }

  case core::node::NodeKind::Assignment: {
    auto *assign = static_cast<parser::node::statement::AssignmentNode *>(node);
    resolve(unit, assign->target);
    resolve(unit, assign->value);
    break;
  }

  default: break;
  }
}

void Resolver::resolve_ast(CompilationUnit &unit) {
  for (auto *node : unit.ast.get_nodes()) { resolve(unit, node); }
}

} // namespace resolver
