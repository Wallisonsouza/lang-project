#pragma once
#include "core/AST.hpp"
#include "core/node/Node.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <string>

struct TreeLayout {
  std::ostream &out;
  std::vector<bool> ancestors_alive;

  explicit TreeLayout(std::ostream &out);

  void begin_node(bool is_last);
  void end_node();
  void print_vertical_padding(size_t lines);
};

struct ASTDebug {

  std::ostream &out;
  TreeLayout tree;

  explicit ASTDebug(std::ostream &out = std::cout);

  void dump_ast(const AST &ast);
  void debug_labeled_child(const char *label, const core::node::Node *child, bool is_last);
  void debug_node(const core::node::Node *node, bool is_last, const std::string header = "");

  void debug_number_literal(const parser::node::NumberLiteralNode *node);
  void debug_string_literal(const parser::node::StringLiteralNode *node);
  void debug_bool_literal(const parser::node::BoolLiteralNode *node);
  void debug_char_literal(const parser::node::CharLiteralNode *node);
  void debug_null_literal(const parser::node::NullLiteralNode *node);
  void debug_identifier(const core::node::IdentifierNode *node);
  void debug_member_access(const parser::node::MemberAccessNode *node);
  void debug_import(const parser::node::statement::ImportNode *node);
  void debug_type(const core::node::TypeNode *node);
  void debug_variable_declaration(const parser::node::VariableDeclarationNode *node);
  void debug_binary_expression(const parser::node::BinaryExpressionNode *node);
  void debug_function_call(const parser::node::FunctionCallNode *node);
  void debug_expression_statement(const core::node::ExpressionStatementNode *node);
  void debug_native_function_declaration(const core::node::NativeFunctionDeclarationNode *node);
  void debug_path_expression(const parser::node::statement::PathExprNode *node);
  void debug_if_statement(const parser::node::IfStatementNode *node);
  void debug_assing_node(const parser::node::statement::AssignmentNode *node);
  void debug_block_node(const parser::node::BlockNode *node);

  void debug_children(const std::vector<const core::node::Node *> &children);
};