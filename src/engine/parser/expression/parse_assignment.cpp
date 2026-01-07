#include "core/node/Type.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_assignment(core::node::ExpressionNode *target) {

  if (!stream.match(core::token::TokenKind::Assign)) { return nullptr; }

  auto *value = parse_expression();

  if (!value) {
    // unit.diagnostics.emit(
    //     {DiagnosticCode::InvalidAssignment, stream.last_slice(), {}}, unit);
    // return nullptr;
  }

  return unit.ast.create_node<parser::node::statement::AssignmentNode>(target, value);
}
