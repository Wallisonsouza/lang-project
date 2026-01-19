#pragma once
#include "core/node/Modifier.hpp"
#include "core/node/Type.hpp"
#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "engine/CompilationUnit.hpp"
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
  void synchronize_statement();
  void synchronize_function();

  using BoundaryFn = std::function<bool(core::token::TokenKind)>;

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

  ParserResult<parser::node::BlockStatementNode> parse_block_statement();
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

      auto *tok = unit.tokens.peek();
      if (tok) {
        debug::engine::dump_token(*tok);
      }

      if (stmt) {
        unit.ast.add_root(stmt);
      }

      consume_statement_separators();
    }
  }

  void consume_statement_separators() {
    while (unit.tokens.match(core::token::TokenKind::NEW_LINE) ||
           unit.tokens.match(core::token::TokenKind::Semicolon))
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

  ParserResult<core::node::ParameterListNode>
  parse_list(core::token::TokenKind open_token,
             core::token::TokenKind close_token,
             core::token::TokenKind separator_token,
             std::function<core::node::PatternNode *()> parse_element) {

    std::vector<core::node::PatternNode *> elements;

    // '('
    if (!unit.tokens.match(open_token)) {
      auto desc = unit.context.descriptor_table.lookup_by_kind(open_token);
      report_error(DiagnosticCode::ExpectedToken,
                   desc ? desc->name : "opening token");
      return ParserResult<core::node::ParameterListNode>::error();
    }

    bool expect_element = true;

    while (!unit.tokens.is_end()) {

      // ignora newlines internos
      while (unit.tokens.peek(core::token::TokenKind::NEW_LINE))
        unit.tokens.advance();

      // fechamento correto
      if (unit.tokens.peek(close_token)) {
        unit.tokens.advance();
        return ParserResult<core::node::ParameterListNode>::success(
            unit.ast.create_node<core::node::ParameterListNode>(
                std::move(elements)));
      }

      auto *current = unit.tokens.peek();
      if (!current)
        break;

      // ---- ESPERANDO ELEMENTO ----
      if (expect_element) {

        // token que claramente NÃO pode iniciar um elemento
        // ex: '{', 'fn', 'let', etc.
        auto *el = parse_element();
        if (!el) {
          report_error(DiagnosticCode::ExpectedIdentifier,
                       "expected parameter");
          return ParserResult<core::node::ParameterListNode>::error();
        }

        elements.push_back(el);
        expect_element = false;
        continue;
      }

      // ---- ESPERANDO ',' OU ')' ----
      if (unit.tokens.match(separator_token)) {
        expect_element = true;
        continue;
      }

      // aqui sabemos que:
      // - não é ','
      // - não é ')'
      // então decidimos a mensagem com base no token encontrado

      if (current->descriptor->kind == core::token::TokenKind::OpenBrace) {
        report_error(DiagnosticCode::ExpectedToken,
                     "expected ')' before function body");
      } else {
        auto sep_desc =
            unit.context.descriptor_table.lookup_by_kind(separator_token);

        report_error(DiagnosticCode::ExpectedToken,
                     sep_desc ? sep_desc->name
                              : "separator between parameters");
      }

      return ParserResult<core::node::ParameterListNode>::error();
    }

    // EOF antes de fechar a lista
    report_error(DiagnosticCode::ExpectedToken,
                 "unterminated parameter list, missing ')'");
    return ParserResult<core::node::ParameterListNode>::error();
  }
};
