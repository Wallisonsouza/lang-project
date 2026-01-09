#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_statement() {
  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  // import
  if (auto *import_stmt = parse_import_statement()) { return import_stmt; }

  if (tok->descriptor->kind == core::token::TokenKind::IfKeyword) { return parse_if_statement(); }

  // variável
  if (tok->descriptor->kind == core::token::TokenKind::Value || tok->descriptor->kind == core::token::TokenKind::Variable) { return parse_variable_declaration(); }

  // função
  if (tok->descriptor->kind == core::token::TokenKind::FunctionKeyword) {
    // return parse_function_declaration();
  }

  // expressão
  auto *expr = parse_expression();

  if (!expr) { return nullptr; }

  // 🔴 FILTRO IMPORTANTE
  // switch (expr->kind) {
  // case core::node::NodeKind::FunctionCall:
  // case core::node::NodeKind::Assignment:
  //   break; // OK
  //   // default:
  //   // unit.diagnostics.emit({DiagnosticCode::InvalidExpressionStatement,
  //   // unit.tokens.last_slice(), {}}, unit); return nullptr;
  // }

  auto *stmt = unit.ast.create_node<core::node::ExpressionStatementNode>(expr);

  if (unit.tokens.match(core::token::TokenKind::Semicolon)) {

  } else {
    // unit.diagnostics.emit({DiagnosticCode::ExpectedToken,
    // unit.tokens.last_slice(), {.found = end, .expected =
    // core::token::TokenKind::Semicolon}}, unit);
  }

  return stmt;
}
