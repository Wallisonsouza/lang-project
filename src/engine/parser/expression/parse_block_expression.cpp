#include "engine/parser/parser.hpp"

parser::node::ReturnStatementNode *Parser::parse_return_statement() {

  auto return_tok = unit.tokens.match(core::token::TokenKind::ReturnKeyword);

  core::node::ExpressionNode *value = nullptr;

  if (!unit.tokens.peek(core::token::TokenKind::CloseBrace)) {
    value = parse_expression();

    if (!value) { report_error(DiagnosticCode::ExpectedToken, "expected expression after 'return'"); }
  }

  return unit.ast.create_node<parser::node::ReturnStatementNode>(value);
}

parser::node::BlockExpressionNode *Parser::parse_block_expression() {
  if (!unit.tokens.match(core::token::TokenKind::OpenBrace)) return nullptr;

  std::vector<core::node::StatementNode *> statements;
  core::node::ExpressionNode *tail_expr = nullptr;

  while (true) {

    // fim normal do bloco
    if (unit.tokens.match(core::token::TokenKind::CloseBrace)) break;

    // EOF inesperado
    if (unit.tokens.is_end()) {
      auto desc = unit.context.descriptor_table.lookup_by_kind(core::token::TokenKind::CloseBrace);
      report_error(DiagnosticCode::ExpectedToken, desc->name);
      break;
    }

    if (unit.tokens.peek(core::token::TokenKind::ReturnKeyword)) {
      auto *ret = parse_return_statement();
      statements.push_back(ret);

      // nada pode vir depois de return
      if (!unit.tokens.match(core::token::TokenKind::CloseBrace)) {
        report_error(DiagnosticCode::UnexpectedToken, "unexpected tokens after return");
        synchronize_statement();
      }
      break;
    }

    // tenta statement normal
    if (!tail_expr) {
      if (auto *stmt = parse_statement()) {
        statements.push_back(stmt);
        continue;
      }
    }

    // se já temos tail expression, erro
    if (tail_expr) {
      report_error(DiagnosticCode::UnexpectedToken, "only one tail expression is allowed in a block");
      synchronize_statement();
      continue;
    }

    // tenta expressão final
    auto *expr = parse_expression();
    if (!expr) {
      report_error(DiagnosticCode::ExpectedToken, "expected expression or '}'");
      synchronize_statement();
      continue;
    }

    tail_expr = expr;

    // após tail expression só pode fechar bloco
    if (!unit.tokens.peek(core::token::TokenKind::CloseBrace)) {
      report_error(DiagnosticCode::UnexpectedToken, "unexpected tokens after tail expression");
      synchronize_statement();
    }
  }

  return unit.ast.create_node<parser::node::BlockExpressionNode>(std::move(statements), tail_expr);
}
