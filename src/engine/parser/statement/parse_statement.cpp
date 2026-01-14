#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_statement() {
  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {

  case core::token::TokenKind::ImportKeyword: return parse_import_statement();

  case core::token::TokenKind::IfKeyword: return parse_if_statement();

  case core::token::TokenKind::ReturnKeyword: return parse_return_statement();

  case core::token::TokenKind::ValueKeyword:
  case core::token::TokenKind::Variable: return parse_variable_declaration();

  case core::token::TokenKind::FunctionKeyword: return parse_function_declaration();

  default: break;
  }

  if (auto *expr = parse_expression()) { return unit.ast.create_node<core::node::ExpressionStatementNode>(expr); }

  return nullptr;
}
