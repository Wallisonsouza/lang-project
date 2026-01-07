#pragma once
#include "core/module/scope.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"

struct Resolver {

  core::Scope *current_scope;
  CompilationUnit &unit;

  explicit Resolver(CompilationUnit &unit, core::Scope *global) : unit(unit), current_scope(global) {}

  void resolve(core::node::Node *node);
  void push_scope();
  void pop_scope();

  void resolve_function_call(parser::node::FunctionCallNode *node);
  void resolve_identifier(parser::node::IdentifierNode *node);
  void resolve_binary_expression(parser::node::BinaryExpressionNode *node);
  void resolve_if_statement(parser::node::IfStatementNode *node);
  void resolve_variable_declaration(parser::node::VariableDeclarationNode *node);
  void resolve_native_function_declaration(core::node::NativeFunctionDeclarationNode *node);
  void resolve_block(parser::node::BlockNode *node);
  void resolve_path(parser::node::statement::PathExprNode *node);
  void resolve_import_node(parser::node::statement::ImportNode *node);
  void resolve_ast();
};