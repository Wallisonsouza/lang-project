#include "Resolver.hpp"
#include <iostream>

void Resolver::resolve(core::node::Node *node) {

  if (!node) return;

  switch (node->kind) {

  case core::node::NodeKind::NumberLiteral:
  case core::node::NodeKind::StringLiteral:
  case core::node::NodeKind::BooleanLiteral: return;

  case core::node::NodeKind::IfExpression: resolve_if_statement(static_cast<parser::node::IfExpressionNode *>(node)); break;

  case core::node::NodeKind::BlockExpression: resolve_block(static_cast<parser::node::BlockExpressionNode *>(node)); break;

  case core::node::NodeKind::BinaryExpression: resolve_binary_expression(static_cast<parser::node::BinaryExpressionNode *>(node)); break;

  case core::node::NodeKind::PathExpression: resolve_path(static_cast<parser::node::statement::PathExprNode *>(node)); break;

  case core::node::NodeKind::Import: resolve_import_node(static_cast<parser::node::statement::ImportNode *>(node)); break;

  case core::node::NodeKind::Identifier: resolve_identifier(static_cast<core::node::IdentifierNode *>(node)); break;

  case core::node::NodeKind::FunctionCall: resolve_function_call(static_cast<parser::node::FunctionCallNode *>(node)); break;

  case core::node::NodeKind::VariableDeclaration: resolve_variable_declaration(static_cast<parser::node::VariableDeclarationNode *>(node)); break;

  case core::node::NodeKind::NativeFunctionDeclaration: resolve_native_function_declaration(static_cast<core::node::NativeFunctionDeclarationNode *>(node)); break;

  case core::node::NodeKind::ExpressionStatement: resolve_expression_statement(static_cast<core::node::ExpressionStatementNode *>(node)); break;

  case core::node::NodeKind::Assignment: {
    auto *assign = static_cast<parser::node::statement::AssignmentNode *>(node);
    resolve(assign->target);
    resolve(assign->value);
    break;
  }

  default: break;
  }
}

void Resolver::resolve_ast() {
  for (auto *node : unit.ast.get_nodes()) { resolve(node); }
}

void Resolver::push_scope() {
  current_scope = unit.scopes.create_scope(current_scope);
  std::cout << "[push] scope=" << current_scope << " parent=" << current_scope->parent << "\n";
}

void Resolver::pop_scope() {
  std::cout << "[pop ] scope=" << current_scope << "\n";
  current_scope = current_scope->parent;
}
