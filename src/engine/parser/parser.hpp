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

  static ParserResult success(NodeType *n) { return ParserResult{ParserResultCode::Success, n}; }

  static ParserResult error() { return ParserResult{ParserResultCode::Error, nullptr}; }
};

struct Parser {
  CompilationUnit &unit;

  core::ast::TypeNode *parse_type();

private:
  void recover_until(RecoverBoundary boundaries);
  using BoundaryFn = std::function<bool(TokenKind)>;

  void recover_until(BoundaryFn boundary);

  core::ast::ASTExpressionNode *parse_assignment(core::ast::ASTExpressionNode *target);
  core::ast::ASTExpressionNode *finish_call(core::ast::ASTExpressionNode *callee);
  core::ast::ASTExpressionNode *finish_member(core::ast::ASTExpressionNode *base);
  core::ast::ASTExpressionNode *finish_index(core::ast::ASTExpressionNode *base);
  core::ast::Modifiers parse_modifiers();
  std::vector<core::ast::PatternNode *> parse_function_parameters();

  std::vector<core::ast::PatternNode *> parse_parameter_list();

public:
  parser::node::ReturnStatementNode *parse_return_statement();
  core::ast::ASTExpressionNode *parse_path_expression();
  core::ast::ASTExpressionNode *parse_expression();
  core::ast::ASTExpressionNode *parse_postfix_expression();
  core::ast::ASTExpressionNode *parse_primary_expression();
  core::ast::ASTExpressionNode *parse_binary_expression(int min_precedence, core::ast::ASTExpressionNode *lef);

  core::ast::ASTStatementNode *parse_statement();
  core::ast::ASTStatementNode *parse_import_statement();

  core::ast::ASTStatementNode *parse_variable_declaration();
  core::ast::ASTStatementNode *parse_function_declaration();
  core::ast::ASTStatementNode *parse_if_statement();

  parser::node::BlockStatementNode *parse_block_statement();
  core::ast::PatternNode *parse_function_parameter();

  core::ast::ASTExpressionNode *parse_number_literal();
  core::ast::ASTExpressionNode *parse_string_literal();
  core::ast::IdentifierNode *parse_identifier_name();
  core::ast::ASTExpressionNode *parse_grouped_expression();
  core::ast::ASTExpressionNode *parse_path_segment(core::ast::ASTExpressionNode *base);
  core::ast::ASTExpressionNode *parse_index_access(core::ast::ASTExpressionNode *base);

  core::ast::PatternNode *parse_pattern(core::ast::Modifiers mods);

  void parse_program() {

    consume_statement_separators();

    while (!unit.tokens.is_end()) {

      auto *stmt = parse_statement();

      if (stmt) { unit.ast.add_root(stmt); }

      consume_statement_separators();
    }
  }

  void consume_statement_separators() { while (unit.tokens.match(TokenKind::NEW_LINE) || unit.tokens.match(TokenKind::SEMI_COLON)); }

  void report_error(DiagnosticCode code, const std::string &expected, const SourceSlice &slice_override = SourceSlice{}) {

    auto *diag = unit.diagns.create(code, unit.tokens.peek_slice());
    diag->set_expected(expected);

    if (auto current = unit.tokens.peek()) { diag->set_found(unit.source.buffer.get_text(current->slice.span)); }
  }

  template <typename ErrorNodeT> ErrorNodeT *make_error(DiagnosticCode code, const std::string &message, const SourceSlice &slice) {
    report_error(code, message);
    recover_until(RecoverBoundary::Function);

    return unit.ast.create_node<ErrorNodeT>(slice);
  }
};
