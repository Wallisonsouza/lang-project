#include "engine/parser/parser.hpp"

/// I'm going crazy.
core::node::PatternNode *Parser::parse_pattern(core::node::Modifiers mods) {

  auto start = unit.tokens.peek_slice();

  auto *id_node = parse_identifier_name();
  if (!id_node) {
    report_error(DiagnosticCode::ExpectedIdentifier, "identifier");

    unit.tokens.advance();
    return unit.ast.create_node<core::node::PatternErrorNode>(start, mods);
  }

  core::node::TypeNode *type_node = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Colon)) {
    type_node = parse_type();
    if (!type_node) {
      report_error(DiagnosticCode::ExpectedType, "type");

      return unit.ast.create_node<core::node::PatternErrorNode>(start, mods);
    }
  }

  core::node::ExpressionNode *value_node = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Assign)) {
    value_node = parse_expression();
    if (!value_node) {
      report_error(DiagnosticCode::ExpectedExpression, "expression after '='");

      return unit.ast.create_node<core::node::PatternErrorNode>(start, mods);
    }
  } else {
    // auto *exp = parse_expression();
    // if (exp) {
    //   report_error(DiagnosticCode::ExpectedToken, "expected '=' in pattern",
    //                exp->slice);

    //   return unit.ast.create_node<core::node::PatternErrorNode>(start, mods);
    // }
  }

  return unit.ast.create_node<core::node::PatternNode>(id_node, type_node,
                                                       value_node, mods);
}
