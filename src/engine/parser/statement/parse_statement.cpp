#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_statement() {
  auto *tok = stream.peek();
  if (!tok) return nullptr;

  // import
  if (auto *import_stmt = parse_import_statement()) { return import_stmt; }

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
  switch (expr->kind) {
  case core::node::NodeKind::FunctionCall:
  case core::node::NodeKind::Assignment: break; // OK
  default: unit.diagnostics.emit({DiagnosticCode::InvalidExpressionStatement, stream.last_slice(), {}}, unit); return nullptr;
  }

  auto *stmt = unit.ast.create_node<core::node::ExpressionStatementNode>(expr);

  auto *end = stream.peek();
  if (end && end->descriptor->kind == core::token::TokenKind::Semicolon) {
    stream.advance();
  } else {
    unit.diagnostics.emit({DiagnosticCode::ExpectedToken, stream.last_slice(), {.found = end, .expected = core::token::TokenKind::Semicolon}}, unit);
  }

  return stmt;
}
