#pragma once
#include "core/node/Modifier.hpp"
#include "core/node/Node.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "diagnostic/Diagnostic.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <iostream>

struct Parser {
  CompilationUnit &unit;
  core::token::TokenStream &stream;

  core::node::TypeNode *parse_type();

private:
  core::node::ExpressionNode *parse_assignment(core::node::ExpressionNode *target);
  core::node::ExpressionNode *finish_call(core::node::ExpressionNode *callee);
  core::node::ExpressionNode *finish_member(core::node::ExpressionNode *base);
  core::node::ExpressionNode *finish_index(core::node::ExpressionNode *base);
  core::node::Modifiers parse_modifiers();

  std::vector<core::node::FunctionParameterNode *> parse_parameter_list();

public:
  core::node::ExpressionNode *parse_path_expression();
  core::node::ExpressionNode *parse_expression();
  core::node::ExpressionNode *parse_postfix_expression();
  core::node::ExpressionNode *parse_primary_expression();
  core::node::ExpressionNode *parse_binary_expression(int min_precedence, core::node::ExpressionNode *lef);

  core::node::StatementNode *parse_statement();
  core::node::StatementNode *parse_import_statement();
  core::node::StatementNode *parse_if_statement();
  core::node::StatementNode *parse_variable_declaration();
  core::node::StatementNode *parse_function_declaration();
  parser::node::BlockNode *parse_block();
  core::node::FunctionParameterNode *parse_function_parameter();

  core::node::Node *call_parser() {

    auto tok = stream.peek();
    if (!tok) return nullptr;

    if (tok->descriptor->kind == core::token::TokenKind::Colon) { return parse_type(); }

    return parse_statement();
  }

  void report_error(const DiagnosticCode code, const Slice &slice, DiagnosticToken opt = {}) { unit.diagns.report({.code = code, .slice = slice, .token = opt}); };
};
