#pragma once
#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"

#include "engine/parser/error/recover.hpp"
#include "engine/parser/node/statement_nodes.hpp"

enum class ParserResultCode { Success, Error };

template <typename NodeType> struct ParserResult {
  ParserResultCode code;
  NodeType *node;

  static ParserResult success(NodeType *n) {
    return ParserResult{ParserResultCode::Success, n};
  }

  static ParserResult error() {
    return ParserResult{ParserResultCode::Error, nullptr};
  }
};

struct Parser {
  CompilationUnit &unit;

  core::node::TypeNode *parse_type();

private:
  void recover_until(RecoverBoundary boundaries);
  using BoundaryFn = std::function<bool(TokenKind)>;

  void recover_until(BoundaryFn boundary);

  core::node::ExpressionNode *
  parse_assignment(core::node::ExpressionNode *target);
  core::node::ExpressionNode *finish_call(core::node::ExpressionNode *callee);
  core::node::ExpressionNode *finish_member(core::node::ExpressionNode *base);
  core::node::ExpressionNode *finish_index(core::node::ExpressionNode *base);
  core::node::Modifiers parse_modifiers();
  std::vector<core::node::PatternNode *> parse_function_parameters();

  std::vector<core::node::PatternNode *> parse_parameter_list();

public:
  parser::node::ReturnStatementNode *parse_return_statement();
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
  core::node::StatementNode *parse_if_statement();

  parser::node::BlockStatementNode *parse_block_statement();
  core::node::PatternNode *parse_function_parameter();

  core::node::ExpressionNode *parse_number_literal();
  core::node::ExpressionNode *parse_string_literal();
  core::node::IdentifierNode *parse_identifier_name();
  core::node::ExpressionNode *parse_grouped_expression();
  core::node::ExpressionNode *
  parse_path_segment(core::node::ExpressionNode *base);
  core::node::ExpressionNode *
  parse_index_access(core::node::ExpressionNode *base);

  core::node::PatternNode *parse_pattern(core::node::Modifiers mods);

  void parse_program() {

    consume_statement_separators();

    while (!unit.tokens.is_end()) {

      auto *stmt = parse_statement();

      if (stmt) {
        unit.ast.add_root(stmt);
      }

      consume_statement_separators();
    }
  }

  void consume_statement_separators() {
    while (unit.tokens.match(TokenKind::NEW_LINE) ||
           unit.tokens.match(TokenKind::SEMI_COLON))
      ;
  }

  void report_error(DiagnosticCode code, const std::string &expected,
                    const SourceSlice &slice_override = SourceSlice{}) {

    auto *diag = unit.diagns.create(code, unit.tokens.peek_slice());
    diag->set_expected(expected);

    if (auto current = unit.tokens.peek()) {
      diag->set_found(unit.source.buffer.get_text(current->slice.span));
    }
  }

  template <typename ErrorNodeT>
  ErrorNodeT *make_error(DiagnosticCode code, const std::string &message,
                         const SourceSlice &slice) {
    report_error(code, message);
    recover_until(RecoverBoundary::Function);

    return unit.ast.create_node<ErrorNodeT>(slice);
  }

  core::node::ParameterListNode *
  parse_list(TokenKind open_token, TokenKind close_token,
             TokenKind separator_token,
             std::function<core::node::PatternNode *()> parse_element);
};
