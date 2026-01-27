#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_primary_expression() {

  auto *tok = unit.tokens.peek();
  if (!tok)
    return nullptr;

  switch (tok->descriptor->kind) {

  case TokenKind::NumberLiteral:
    return parse_number_literal();

  case TokenKind::StringLiteral:
    return parse_string_literal();

  case TokenKind::Identifier:
    return parse_identifier_name();

  case TokenKind::OpenParen:
    return parse_grouped_expression();

  default:
    return nullptr;
  }
}