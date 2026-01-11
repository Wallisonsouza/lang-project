#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "core/token/Location.hpp"
#include "core/token/Token.hpp"
#include "diagnostic/diagnostic_code.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_if_statement() {
  auto *if_tok = unit.tokens.try_match(core::token::TokenKind::IfKeyword);
  if (!if_tok) return nullptr;

  auto *condition = parse_expression();

  if (!condition) { return report_error(DiagnosticCode::IfConditionMissing, unit.source.buffer.get_text(if_tok->slice.span), if_tok->slice); }

  if (condition->kind == core::node::NodeKind::Assignment) {
    //
    return report_error(DiagnosticCode::IfConditionAssignment, unit.source.buffer.get_text(if_tok->slice.span), condition->slice);
  }

  auto *then_block = parse_block();
  if (!then_block) {
    auto *diag = unit.diagns.create(DiagnosticCode::ThenBlockMissing, unit.tokens.last_slice());
    diag->set_expected(unit.source.buffer.get_text(if_tok->slice.span));
    diag->context.set("block", "then");
    synchronize_statement();

    // then_block = error_recovery::make_error_node<parser::node::BlockNode>(unit);
  }

  parser::node::BlockNode *else_block = nullptr;
  if (unit.tokens.match(core::token::TokenKind::ElseKeyword)) {
    else_block = parse_block();
    if (!else_block || else_block->statements.empty()) {
      auto *diag = unit.diagns.create(DiagnosticCode::ElseBlockMissing, unit.tokens.last_slice());
      diag->set_expected(unit.source.buffer.get_text(if_tok->slice.span));
      diag->context.set("block", "else");

      // else_block = error_recovery::make_error_node<parser::node::BlockNode>(unit);
    }
  }

  return unit.ast.create_node<parser::node::IfStatementNode>(condition, then_block, else_block);
}
