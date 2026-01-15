#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "diagnostic/diagnostic_code.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

std::vector<core::node::PatternNode *> Parser::parse_function_parameters() {
  std::vector<core::node::PatternNode *> params;

  while (!unit.tokens.peek(core::token::TokenKind::CloseParen) && !unit.tokens.is_end()) {
    auto mods = core::node::Modifiers{};
    auto *param = parse_pattern(mods);
    if (!param) {
      synchronize_parameter();
      if (!unit.tokens.match(core::token::TokenKind::Comma)) break;
      continue;
    }

    params.push_back(param);

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
  }

  // Abre bloco (função consome o '{')
  if (!unit.tokens.match(core::token::TokenKind::OpenBrace)) {
    report_error(DiagnosticCode::ExpectedToken, "expected '{' to start function body");
    synchronize_statement();
    return nullptr;
  }

  // Parseia statements e tail expression, mas não fecha o '}'
  auto *body = parse_block_statement();
  if (!body) {
    synchronize_statement();
    return nullptr;
  }

  // Fecha bloco (função consome o '}')
  if (!unit.tokens.match(core::token::TokenKind::CloseBrace)) {
    report_error(DiagnosticCode::ExpectedToken, "expected '}' to close function body");
    synchronize_statement();
    return nullptr;
  }

  return unit.ast.create_node<parser::node::FunctionDeclarationNode>(identifier, params, return_type, body);
}
