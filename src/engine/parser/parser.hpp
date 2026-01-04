#pragma once
#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"

struct Parser {
  CompilationUnit &unit;
  core::token::TokenStream &stream;

  core::node::TypeNode *parse_type();

private:
  core::node::ExpressionNode *
  parse_assignment(core::node::ExpressionNode *target);
  core::node::ExpressionNode *finish_call(core::node::ExpressionNode *callee);
  core::node::ExpressionNode *finish_member(core::node::ExpressionNode *base);
  core::node::ExpressionNode *finish_index(core::node::ExpressionNode *base);
  core::node::Modifiers parse_modifiers();

public:
  core::node::ExpressionNode *parse_path_expression();
  core::node::ExpressionNode *parse_expression();
  core::node::ExpressionNode *parse_postfix_expression();
  core::node::ExpressionNode *parse_primary_expression();
  core::node::ExpressionNode *
  parse_binary_expression(int min_precedence, core::node::ExpressionNode *lef);

  core::node::StatementNode *parse_statement();
  core::node::StatementNode *parse_import_statement();
  core::node::StatementNode *parse_variable_declaration();
  core::node::StatementNode *parse_function_declaration();
};
