#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"
#include <iostream>

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
  if (!then_block) {
    std::cout << "if não tem um bloco";
    // unit.diagnostics.emit({DiagnosticCode::NoCode, unit.tokens.last_slice(), {}});
    return nullptr;
  }

  parser::node::BlockNode *else_block = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Else)) {
    else_block = parse_block();
    if (!else_block) {
      // unit.diagnostics.emit({DiagnosticCode::NoCode, unit.tokens.last_slice(), {}});
      return nullptr;
    }
  }

  auto *node = unit.ast.create_node<parser::node::IfStatementNode>(condition, then_block, else_block);

  return node;
}
