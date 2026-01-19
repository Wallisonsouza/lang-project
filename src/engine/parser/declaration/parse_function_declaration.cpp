#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

parser::node::ReturnStatementNode *Parser::parse_return_statement() {
  unit.tokens.match(core::token::TokenKind::RETURN_KEYWORD);

  // return sem valor
  if (unit.tokens.peek(core::token::TokenKind::CLOSE_BRACE) ||
      unit.tokens.peek(core::token::TokenKind::NEW_LINE)) {
    return unit.ast.create_node<parser::node::ReturnStatementNode>(nullptr);
  }

  auto *value = parse_expression();
  if (!value) {
    report_error(DiagnosticCode::ExpectedToken,
                 "expected expression after 'return'");
    unit.tokens.advance();
  }

  return unit.ast.create_node<parser::node::ReturnStatementNode>(value);
}

//

ParserResult<parser::node::BlockStatementNode> Parser::parse_block_statement() {

  std::vector<core::node::StatementNode *> statements;

  if (!unit.tokens.match(core::token::TokenKind::OpenBrace)) {

    report_error(DiagnosticCode::ExpectedToken, "'{' to start block");
    return ParserResult<parser::node::BlockStatementNode>::error();
  }

  consume_statement_separators();

  while (!unit.tokens.is_end() &&
         !unit.tokens.peek(core::token::TokenKind::CLOSE_BRACE)) {

    auto *stmt = parse_statement();
    if (stmt) {
      statements.push_back(stmt);
    } else {
      unit.tokens.advance();
    }

    consume_statement_separators();
  }

  // '}'
  if (!unit.tokens.match(core::token::TokenKind::CLOSE_BRACE)) {
    report_error(DiagnosticCode::ExpectedToken, "'}' to close block");
    return ParserResult<parser::node::BlockStatementNode>::error();
  }

  return ParserResult<parser::node::BlockStatementNode>::success(
      unit.ast.create_node<parser::node::BlockStatementNode>(
          std::move(statements)));
}

core::node::StatementNode *Parser::parse_function_declaration() {
  auto start = unit.tokens.peek_slice();

  if (!unit.tokens.match(core::token::TokenKind::FUNCTION_KEYWORD)) {
    return nullptr;
  }

  auto *name = parse_identifier_name();

  if (!name) {
    report_error(DiagnosticCode::ExpectedIdentifier, "function name");
    synchronize_function();
    return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
  }

  auto params = parse_list(
      core::token::TokenKind::OpenParen, core::token::TokenKind::CloseParen,
      core::token::TokenKind::COMMA, [&]() { return parse_pattern({}); });

  if (params.code == ParserResultCode::Error) {
    synchronize_function();
    return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
  }

  core::node::TypeNode *return_type = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Arrow)) {
    return_type = parse_type();
    if (!return_type) {
      report_error(DiagnosticCode::ExpectedType, "return type");
      synchronize_function();
      return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
    }
  }

  auto body = parse_block_statement();

  if (body.code == ParserResultCode::Error) {
    synchronize_function();
    return unit.ast.create_node<parser::node::FunctionErrorNode>(start);
  }

  return unit.ast.create_node<parser::node::FunctionDeclarationNode>(
      name, params.node->parameters, return_type, body.node);
}