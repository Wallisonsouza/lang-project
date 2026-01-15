#include "core/node/Type.hpp"
#include "engine/parser/parser.hpp"

core::node::PatternNode *Parser::parse_pattern(core::node::Modifiers mods) {

  auto *id_node = parse_identifier_name();
  if (!id_node) {
    report_error(DiagnosticCode::ExpectedIdentifier, "identifier");
    synchronize_statement();
    return nullptr;
  }

  core::node::TypeNode *type_node = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Colon)) {
    type_node = parse_type();
    if (!type_node) {
      report_error(DiagnosticCode::ExpectedType, "type");
      synchronize_statement();
      return nullptr;
    }
  }

  core::node::ExpressionNode *value_node = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Assign)) {
    value_node = parse_expression();
    if (!value_node) {
      report_error(DiagnosticCode::ExpectedExpression, "expression after '='");
      synchronize_statement();
      return nullptr;
    }
  } else {
    auto *exp = parse_expression();
    if (exp) {
      report_error(DiagnosticCode::ExpectedToken, "expected '=' in pattern", exp->slice);
      synchronize_statement();
      return nullptr;
    }
  }

  return unit.ast.create_node<core::node::PatternNode>(id_node, type_node, value_node, mods);
}
