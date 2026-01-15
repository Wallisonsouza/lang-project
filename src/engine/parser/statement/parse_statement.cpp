#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_statement() {
  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  core::node::StatementNode *stmt = nullptr;

  switch (tok->descriptor->kind) {
  case core::token::TokenKind::ImportKeyword: stmt = parse_import_statement(); break;
  case core::token::TokenKind::IfKeyword: stmt = parse_if_statement(); break;
  case core::token::TokenKind::ReturnKeyword: stmt = parse_return_statement(); break;
  case core::token::TokenKind::ValueKeyword:
  case core::token::TokenKind::Variable: stmt = parse_variable_declaration(); break;
  case core::token::TokenKind::FunctionKeyword: stmt = parse_function_declaration(); break;
  default:
    if (auto *expr = parse_expression()) { stmt = unit.ast.create_node<core::node::ExpressionStatementNode>(expr); }
    break;
  }

  if (unit.tokens.peek(core::token::TokenKind::Newline)) { unit.tokens.advance(); }

  return stmt;
}
