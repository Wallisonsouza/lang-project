#pragma once
#include "core/node/Modifier.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "core/token/Location.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"

struct Parser {
  CompilationUnit &unit;

  core::node::TypeNode *parse_type();

private:
  void synchronize_statement();
  void synchronize_parameter();

  core::node::ExpressionNode *parse_assignment(core::node::ExpressionNode *target);
  core::node::ExpressionNode *finish_call(core::node::ExpressionNode *callee);
  core::node::ExpressionNode *finish_member(core::node::ExpressionNode *base);
  core::node::ExpressionNode *finish_index(core::node::ExpressionNode *base);
  core::node::Modifiers parse_modifiers();
  std::vector<core::node::FunctionParameterNode *> parse_function_parameters();

  std::vector<core::node::FunctionParameterNode *> parse_parameter_list();

public:
  parser::node::ReturnStatementNode *parse_return_statement();
  core::node::ExpressionNode *parse_path_expression();
  core::node::ExpressionNode *parse_expression();
  core::node::ExpressionNode *parse_postfix_expression();
  core::node::ExpressionNode *parse_primary_expression();
  core::node::ExpressionNode *parse_binary_expression(int min_precedence, core::node::ExpressionNode *lef);

  core::node::StatementNode *parse_statement();
  core::node::StatementNode *parse_import_statement();

  core::node::StatementNode *parse_variable_declaration();
  core::node::StatementNode *parse_function_declaration();
  core::node::StatementNode *parse_if_statement();

  parser::node::BlockStatementNode *parse_block_statement();
  core::node::FunctionParameterNode *parse_function_parameter();

  core::node::Node *call_parser() {
    if (auto stmt = parse_statement()) return stmt;
    if (auto expr = parse_expression()) return expr;

    return nullptr;
  }

  core::node::ExpressionNode *parse_number_literal();
  core::node::ExpressionNode *parse_string_literal();
  core::node::ExpressionNode *parse_identifier_name();
  core::node::ExpressionNode *parse_grouped_expression();
  core::node::ExpressionNode *parse_path_segment(core::node::ExpressionNode *base);
  core::node::ExpressionNode *parse_index_access(core::node::ExpressionNode *base);

  void generate_ast() {

    while (!unit.tokens.is_end()) {
      auto node = call_parser();
      if (node) {
        unit.ast.add_root(node);
      } else {
        unit.tokens.advance();
      }
    }
  }

  void report_error(DiagnosticCode code, const std::string &expected, const Slice &slice_override = Slice{}) {

    auto *diag = unit.diagns.create(code, unit.tokens.peek_slice());
    diag->set_expected(expected);

    if (auto current = unit.tokens.peek()) { diag->set_found(unit.source.buffer.get_text(current->slice.span)); }
  }

  void synchronize_block() {
    while (!unit.tokens.is_end()) {
      auto *tok = unit.tokens.peek();
      if (!tok) break;

      switch (tok->descriptor->kind) {
      case core::token::TokenKind::CloseBrace:
      case core::token::TokenKind::FunctionKeyword: return;
      default: unit.tokens.advance();
      }
    }
  }
};
