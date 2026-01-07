#include "Resolver.hpp"
#include "core/AST.hpp"
#include "core/node/NodeKind.hpp"

#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"

void Resolver::resolve(core::node::Node *node) {

  if (!node) return;

  switch (node->kind) {

  case core::node::NodeKind::NumberLiteral:
  case core::node::NodeKind::StringLiteral:
  case core::node::NodeKind::BooleanLiteral: return;

  case core::node::NodeKind::IfStatement: resolve_if_statement(static_cast<parser::node::IfStatementNode *>(node)); break;
  case core::node::NodeKind::Block: resolve_block_node(static_cast<parser::node::BlockNode *>(node)); break;
  case core::node::NodeKind::BinaryExpression: resolve_binary_expression(static_cast<parser::node::BinaryExpressionNode *>(node)); break;

  case core::node::NodeKind::PathExpression: resolve_path(static_cast<parser::node::statement::PathExprNode *>(node)); break;

  case core::node::NodeKind::Import: resolve_import_node(static_cast<parser::node::statement::ImportNode *>(node)); break;

  case core::node::NodeKind::Identifier: resolve_identifier(static_cast<parser::node::IdentifierNode *>(node)); break;

  case core::node::NodeKind::FunctionCall: resolve_function_call(static_cast<parser::node::FunctionCallNode *>(node)); break;

  case core::node::NodeKind::VariableDeclaration: resolve_variable_declaration(static_cast<parser::node::VariableDeclarationNode *>(node)); break;
  case core::node::NodeKind::NativeFunctionDeclaration: resolve_native_function_declaration(static_cast<core::node::NativeFunctionDeclarationNode *>(node)); break;
  case core::node::NodeKind::ExpressionStatement: {
    auto *es = static_cast<core::node::ExpressionStatementNode *>(node);
    resolve(es->expr);
    break;
  }

  case core::node::NodeKind::Assignment: {
    auto *assign = static_cast<parser::node::statement::AssignmentNode *>(node);
    resolve(assign->target);
    resolve(assign->value);
    break;
  }

  default: break;
  }
}

void Resolver::resolve_ast(CompilationUnit &unit) {
  for (auto *node : unit.ast.get_nodes()) { resolve(node); }
}
