#include "core/node/Type.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/parser.hpp"

core::node::ExpressionNode *
Parser::parse_assignment(core::node::ExpressionNode *target) {

  if (!unit.tokens.match(TokenKind::Assign)) {
    return nullptr;
  }

  auto start = unit.tokens.peek_slice();

  auto *value = parse_expression();

  if (!value) {
    // unit.diagnostics.emit(
    //     {DiagnosticCode::InvalidAssignment, stream.last_slice(), {}}, unit);
    // return nullptr;
  }

  auto node = unit.ast.create_node<parser::node::statement::AssignmentNode>(
      target, value);
  node->slice = start;
  return node;
}
