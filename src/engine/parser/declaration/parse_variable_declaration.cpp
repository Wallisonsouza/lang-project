#include "core/node/Type.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_variable_declaration() {

  auto mods = parse_modifiers();

  if (mods.order.empty()) return nullptr;

  auto *id_node = parse_identifier_name();

  if (!id_node) {
    synchronize_statement();
    return nullptr;
  }

  if (!unit.tokens.match(core::token::TokenKind::Colon)) {

    auto desc = unit.context.descriptor_table.lookup_by_kind(core::token::TokenKind::Colon);

    report_error(DiagnosticCode::ExpectedColon, desc ? desc->name : ":");

    return nullptr;
  }

  // TYPE
  auto *type_node = parse_type();

  if (!type_node) {

    report_error(DiagnosticCode::ExpectedType, "type");

    return nullptr;
  }

  core::node::ExpressionNode *value_node = nullptr;

  if (unit.tokens.match(core::token::TokenKind::Assign)) {

    value_node = parse_expression();

    if (!value_node) {

      report_error(DiagnosticCode::ExpectedExpression, "expressão");

      return nullptr;
    }
  }

  if (!unit.tokens.match(core::token::TokenKind::Semicolon)) {

    auto desc = unit.context.descriptor_table.lookup_by_kind(core::token::TokenKind::Semicolon);

    report_error(DiagnosticCode::ExpectedToken, desc ? desc->name : ";");

    unit.tokens.match(core::token::TokenKind::Semicolon);
  }

  return unit.ast.create_node<parser::node::VariableDeclarationNode>(static_cast<core::node::IdentifierNode *>(id_node), type_node, value_node, mods);
}