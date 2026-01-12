#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_statement() {
  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  if (auto *import_stmt = parse_import_statement()) return import_stmt;

  if (tok->descriptor->kind == core::token::TokenKind::ReturnKeyword) return parse_return_statement();

  if (tok->descriptor->kind == core::token::TokenKind::ValueKeyword || tok->descriptor->kind == core::token::TokenKind::Variable) return parse_variable_declaration();

  if (tok->descriptor->kind == core::token::TokenKind::FunctionKeyword) return parse_function_declaration();

  return nullptr;
}
