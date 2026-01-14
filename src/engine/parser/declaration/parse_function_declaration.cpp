#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "diagnostic/diagnostic_code.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

std::vector<core::node::FunctionParameterNode *> Parser::parse_function_parameters() {
  std::vector<core::node::FunctionParameterNode *> params;

  if (unit.tokens.peek(core::token::TokenKind::CloseParen)) return params;

  while (true) {

    auto *param_tok = unit.tokens.match(core::token::TokenKind::Identifier);
    if (!param_tok) {
      report_error(DiagnosticCode::ExpectedIdentifier, "parameter name", unit.tokens.last_slice());
      synchronize_parameter();
      if (!unit.tokens.match(core::token::TokenKind::Comma)) break;
      continue;
    }

    auto *param_name = unit.ast.create_node<core::node::IdentifierNode>(unit.source.buffer.get_text(param_tok->slice.span));

    if (!unit.tokens.match(core::token::TokenKind::Colon)) {
      report_error(DiagnosticCode::ExpectedColon, ":", unit.tokens.peek_slice());
      synchronize_parameter();
      if (!unit.tokens.match(core::token::TokenKind::Comma)) break;
      continue;
    }

    auto *param_type = parse_type();
    if (!param_type) {
      report_error(DiagnosticCode::ExpectedType, "type", unit.tokens.peek_slice());
      synchronize_parameter();
      if (!unit.tokens.match(core::token::TokenKind::Comma)) break;
      continue;
    }

    params.push_back(unit.ast.create_node<core::node::FunctionParameterNode>(param_name, param_type, nullptr));

    if (!unit.tokens.match(core::token::TokenKind::Comma)) break;
  }

  return params;
}

core::node::StatementNode *Parser::parse_function_declaration() {
  if (!unit.tokens.match(core::token::TokenKind::FunctionKeyword)) return nullptr;

  auto *identifier = parse_identifier_name();
  if (!identifier) {
    synchronize_statement();
    return nullptr;
  }

  if (!unit.tokens.match(core::token::TokenKind::OpenParen)) {
    report_error(DiagnosticCode::ExpectedToken, "(");
    synchronize_statement();
    return nullptr;
  }

  auto params = parse_function_parameters();

  if (!unit.tokens.match(core::token::TokenKind::CloseParen)) {
    report_error(DiagnosticCode::ExpectedToken, ")");
    synchronize_statement();
  }

  core::node::TypeNode *return_type = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Arrow)) {
    return_type = parse_type();
    if (!return_type) {
      report_error(DiagnosticCode::ExpectedType, "return type", unit.tokens.last_slice());
      synchronize_statement();
      return nullptr;
    }
  } else {
    auto desc = unit.context.descriptor_table.lookup_by_kind(core::token::TokenKind::Arrow);
    report_error(DiagnosticCode::ExpectedToken, desc->name);
  }

  auto *body = parse_block_expression();
  if (!body) {
    synchronize_statement();
    return nullptr;
  }

  return unit.ast.create_node<parser::node::FunctionDeclarationNode>(static_cast<core::node::IdentifierNode *>(identifier), params, return_type, body);
}
