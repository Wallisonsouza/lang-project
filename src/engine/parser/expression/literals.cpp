#include "core/node/Type.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

core::ast::ASTExpressionNode *Parser::parse_number_literal() {
  Token *token = unit.tokens.match(TokenKind::NumberLiteral);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);
  try {
    double value = std::stod(text);
    return unit.ast.create_node<parser::node::NumberLiteralNode>(value);
  } catch (const std::exception &) { return nullptr; }
}

core::ast::ASTExpressionNode *Parser::parse_string_literal() {

  Token *token = unit.tokens.match(TokenKind::StringLiteral);
  if (!token) return nullptr;

  std::string text = unit.source.buffer.get_text(token->slice.span);

  return unit.ast.create_node<parser::node::StringLiteralNode>(text);
}

core::ast::IdentifierNode *Parser::parse_identifier_name() {

  Token *token = unit.tokens.match(TokenKind::Identifier);
  if (!token) return nullptr;

  auto *node = unit.ast.create_node<core::ast::IdentifierNode>(unit.source.buffer.get_text(token->slice.span));
  node->slice = token->slice;

  return node;
}

core::ast::ASTExpressionNode *Parser::parse_grouped_expression() {

  auto *open = unit.tokens.match(TokenKind::OpenParen);
  if (!open) return nullptr;

  core::ast::ASTExpressionNode *expr = parse_expression();
  if (!expr) { return nullptr; }

  auto *close = unit.tokens.match(TokenKind::CloseParen);
  if (!close) { return nullptr; }

  return expr;
}

// a.b.c.d  -> PathExprNode(base=PathExprNode(base=IdentifierNode(a), b), c), d)
core::ast::ASTExpressionNode *Parser::parse_path_segment(core::ast::ASTExpressionNode *base) {

  auto *dot = unit.tokens.match(TokenKind::Dot);
  if (!dot) return nullptr;

  auto *field = parse_identifier_name();

  if (!field) { return nullptr; }

  return unit.ast.create_node<parser::node::statement::PathExprNode>(base, field);
}

// a[b] -> IndexAccessNode(base=a, index=b)
core::ast::ASTExpressionNode *Parser::parse_index_access(core::ast::ASTExpressionNode *base) {

  auto *open = unit.tokens.match(TokenKind::OPEN_BRACKET);
  if (!open) return nullptr; // erro: '[' esperado

  core::ast::ASTExpressionNode *index_expr = parse_expression();
  if (!index_expr) return nullptr; // erro: expressão esperada dentro de '[]'

  auto *close = unit.tokens.match(TokenKind::CLOSE_BRACKET);
  if (!close) return nullptr; // erro: ']' esperado

  return unit.ast.create_node<parser::node::IndexAccessNode>(base, index_expr);
}
