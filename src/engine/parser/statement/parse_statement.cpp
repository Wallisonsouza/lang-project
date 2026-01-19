#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_statement() {

  auto *tok = unit.tokens.peek();
  if (!tok)
    return nullptr;

  switch (tok->descriptor->kind) {

  case core::token::TokenKind::IMPORT_KEYWORD:
    return parse_import_statement();

  case core::token::TokenKind::IF_KEYWORD:
    return parse_if_statement();

  case core::token::TokenKind::RETURN_KEYWORD:
    return parse_return_statement();

  case core::token::TokenKind::VALUE_KEYWORD:
  case core::token::TokenKind::CONST_KEYWORD:
    return parse_variable_declaration();

  case core::token::TokenKind::FUNCTION_KEYWORD:
    return parse_function_declaration();

  default:
    if (auto *expr = parse_expression()) {
      return unit.ast.create_node<core::node::ExpressionStatementNode>(expr);
    }

    unit.tokens.advance();
    return nullptr;
  }
}
