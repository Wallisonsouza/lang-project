#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_if_statement() {

  if (!unit.tokens.match(core::token::TokenKind::IfKeyword)) return nullptr;

  auto *condition = parse_expression();

  if (!condition) {
    // unit.diagnostics.emit({DiagnosticCode::ExpectedExpression, unit.tokens.last_slice(), {}});
    return nullptr;
  }

  if (condition->kind == core::node::NodeKind::Assignment) {
    // unit.diagnostics.emit({DiagnosticCode::NoCode, unit.tokens.last_slice(), {}});
    return nullptr;
  }

  auto *then_block = parse_block();

  if (!then_block || then_block->statements.empty()) {
    std::cout << "if não tem um bloco";
    // unit.diagnostics.emit({DiagnosticCode::NoCode, unit.tokens.last_slice(), {}});
    return nullptr;
  }

  parser::node::BlockNode *else_block = nullptr;
  if (unit.tokens.match(core::token::TokenKind::ElseKeyword)) {
    std::cout << "else";
    else_block = parse_block();
    if (!else_block) {
      // unit.diagnostics.emit({DiagnosticCode::NoCode, unit.tokens.last_slice(), {}});
      return nullptr;
    }
  }

  auto *node = unit.ast.create_node<parser::node::IfStatementNode>(condition, then_block, else_block);

  return node;
}
