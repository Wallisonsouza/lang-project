#include "core/node/Type.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_number_literal() {
  core::token::Token *token = unit.tokens.match(core::token::TokenKind::NumberLiteral);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);
  try {
    double value = std::stod(text);
    return unit.ast.create_node<parser::node::NumberLiteralNode>(value);
  } catch (const std::exception &) { return nullptr; }
}

core::node::ExpressionNode *Parser::parse_string_literal() {

  core::token::Token *token = unit.tokens.match(core::token::TokenKind::StringLiteral);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);

  return unit.ast.create_node<parser::node::StringLiteralNode>(text);
}

core::node::ExpressionNode *Parser::parse_identifier_name() {

  core::token::Token *token = unit.tokens.match(core::token::TokenKind::Identifier);
  if (!token) return nullptr;

  auto *node = unit.ast.create_node<core::node::IdentifierNode>(unit.source.buffer.get_text(token->slice.span));
  node->slice = token->slice;

  return node;
}

core::node::ExpressionNode *Parser::parse_grouped_expression() {

  auto *open = unit.tokens.match(core::token::TokenKind::OpenParen);
  if (!open) return nullptr;

  core::node::ExpressionNode *expr = parse_expression();
  if (!expr) { return nullptr; }

  auto *close = unit.tokens.match(core::token::TokenKind::CloseParen);
  if (!close) { return nullptr; }

  return expr;
}


// a.b.c.d  -> PathExprNode(base=PathExprNode(base=IdentifierNode(a), b), c), d)
core::node::ExpressionNode *Parser::parse_path_segment(core::node::ExpressionNode *base) {

  auto *dot = unit.tokens.match(core::token::TokenKind::Dot);
  if (!dot) return nullptr;

  auto *field = parse_identifier_name();

  if (!field) { return nullptr; }

  return unit.ast.create_node<parser::node::statement::PathExprNode>(base, field);
}


// a[b] -> IndexAccessNode(base=a, index=b)
core::node::ExpressionNode *Parser::parse_index_access(core::node::ExpressionNode *base) {

  auto *open = unit.tokens.match(core::token::TokenKind::OpenBracket);
  if (!open) return nullptr; // erro: '[' esperado

  core::node::ExpressionNode *index_expr = parse_expression();
  if (!index_expr) return nullptr; // erro: expressão esperada dentro de '[]'

  auto *close = unit.tokens.match(core::token::TokenKind::CloseBracket);
  if (!close) return nullptr; // erro: ']' esperado

  return unit.ast.create_node<parser::node::IndexAccessNode>(base, index_expr);
}
