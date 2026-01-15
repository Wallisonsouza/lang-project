#include "engine/parser/parser.hpp"

parser::node::ReturnStatementNode *Parser::parse_return_statement() {
  unit.tokens.match(core::token::TokenKind::ReturnKeyword);

  core::node::ExpressionNode *value = nullptr;

  if (unit.tokens.peek(core::token::TokenKind::CloseBrace)) { return unit.ast.create_node<parser::node::ReturnStatementNode>(nullptr); }

  value = parse_expression();
  if (!value) {
    report_error(DiagnosticCode::ExpectedToken, "expected expression after 'return'");
    synchronize_block();
  }

  return unit.ast.create_node<parser::node::ReturnStatementNode>(value);
}

parser::node::BlockStatementNode *Parser::parse_block_statement() {
  std::vector<core::node::StatementNode *> statements;

  while (!unit.tokens.is_end() && !unit.tokens.peek(core::token::TokenKind::CloseBrace)) {

    consume_statement_separators();

    auto *stmt = parse_statement();

    if (!stmt) {
      // Se não houver statement, mas o próximo token for '}', apenas encerra o bloco
      if (unit.tokens.peek(core::token::TokenKind::CloseBrace)) break;

      // Caso contrário, é realmente um erro
      report_error(DiagnosticCode::ExpectedToken, "expected statement");
      synchronize_block();
      continue;
    }

    statements.push_back(stmt);
  }

  return unit.ast.create_node<parser::node::BlockStatementNode>(std::move(statements));
}
