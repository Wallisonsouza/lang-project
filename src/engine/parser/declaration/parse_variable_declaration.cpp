#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_variable_declaration() {
  auto mods = parse_modifiers();
  if (mods.order.empty()) return nullptr;

  // identifier
  auto *name_token = unit.tokens.try_match(core::token::TokenKind::Identifier);
  if (!name_token) {
    report_expected(DiagnosticCode::ExpectedIdentifier, core::token::TokenKind::Identifier, unit.tokens.peek());
    return nullptr;
  }

  auto name = unit.source.buffer.get_text(name_token->slice.span);
  auto *id_node = unit.ast.create_node<core::node::IdentifierNode>(name);

  // colon
  if (!unit.tokens.match(core::token::TokenKind::Colon)) {
    report_expected(DiagnosticCode::ExpectedColon, core::token::TokenKind::Colon, unit.tokens.peek());
    return nullptr;
  }

  // type
  auto *type_node = parse_type();
  if (!type_node) {
    report_expected(DiagnosticCode::ExpectedType, core::node::NodeKind::Type, unit.tokens.peek());
    return nullptr;
  }

  core::node::ExpressionNode *value_node = nullptr;

  // optional initializer
  if (unit.tokens.match(core::token::TokenKind::Assign)) {
    value_node = parse_expression();
    if (!value_node) {
      report_expected(DiagnosticCode::ExpectedExpression, core::node::NodeKind::AssignmentExpression, unit.tokens.peek());
      return nullptr;
    }
  }

  // semicolon (obrigatório)
  if (!unit.tokens.match(core::token::TokenKind::Semicolon)) {
    report_expected(DiagnosticCode::ExpectedToken, core::token::TokenKind::Semicolon, unit.tokens.peek());
    return nullptr;
  }

  return unit.ast.create_node<parser::node::VariableDeclarationNode>(id_node, type_node, value_node, mods);
}
