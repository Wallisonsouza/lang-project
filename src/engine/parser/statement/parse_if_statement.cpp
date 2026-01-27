#include "core/node/Type.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_if_statement() {
  // auto *if_tok = unit.tokens.match(TokenKind::IF_KEYWORD);
  // if (!if_tok)
  //   return nullptr;

  // auto *condition = parse_expression();
  // if (!condition) {
  //   report_error(DiagnosticCode::IfConditionMissing,
  //                "expected condition after 'if'", if_tok->slice);

  //   synchronize_statement();
  //   return unit.ast.create_node<parser::node::IfStatementNode>(nullptr,
  //   nullptr,
  //                                                              nullptr);
  // }

  // if (condition->kind == core::node::NodeKind::Assignment) {
  //   report_error(DiagnosticCode::IfConditionAssignment,
  //                "assignment is not allowed in if condition",
  //                condition->slice);
  // }

  // if (!unit.tokens.match(TokenKind::OpenBrace)) {
  //   report_error(DiagnosticCode::ExpectedToken,
  //                "expected '{' after if condition",
  //                unit.tokens.peek_slice());

  //   synchronize_statement();
  //   return unit.ast.create_node<parser::node::IfStatementNode>(
  //       condition, nullptr, nullptr);
  // }

  // auto *then_block = parse_block_statement();

  // if (!unit.tokens.match(TokenKind::CLOSE_BRACE)) {
  //   report_error(DiagnosticCode::ExpectedToken,
  //                "expected '}' to close if block", unit.tokens.peek_slice());
  // }

  // parser::node::BlockStatementNode *else_block = nullptr;

  // if (unit.tokens.match(TokenKind::ELSE_KEYWORD)) {

  //   if (!unit.tokens.match(TokenKind::OpenBrace)) {
  //     report_error(DiagnosticCode::ExpectedToken, "expected '{' after else",
  //                  unit.tokens.peek_slice());
  //     synchronize_statement();
  //   } else {
  //     else_block = parse_block_statement();

  //     if (!unit.tokens.match(TokenKind::CLOSE_BRACE)) {
  //       report_error(DiagnosticCode::ExpectedToken,
  //                    "expected '}' to close else block",
  //                    unit.tokens.peek_slice());
  //     }
  //   }
  // }

  // return unit.ast.create_node<parser::node::IfStatementNode>(
  //     condition, then_block, else_block);

  return nullptr;
}
