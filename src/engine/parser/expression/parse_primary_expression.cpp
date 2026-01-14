#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_primary_expression() {

  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  switch (tok->descriptor->kind) {

  case core::token::TokenKind::NumberLiteral: return parse_number_literal();

  case core::token::TokenKind::StringLiteral: return parse_string_literal();

  case core::token::TokenKind::Identifier: return parse_identifier_name();

  case core::token::TokenKind::OpenParen: return parse_grouped_expression();

  default: return nullptr;
  }
}