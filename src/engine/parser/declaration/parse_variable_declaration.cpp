#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "debug/console/console.hpp"
#include "diagnostic/Diagnostic.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_variable_declaration() {
  auto mods = parse_modifiers();

  if (mods.order.empty()) return nullptr;

  auto *name_token = stream.try_match(core::token::TokenKind::Identifier);

  if (!name_token) {

    // report_error(DiagnosticCode::ExpectedIdentifier, stream.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::Identifier, .found = stream.peek()});

    return nullptr;
  }

  auto name = unit.source.buffer.get_text(name_token->slice.span);

  if (!stream.match(core::token::TokenKind::Colon)) {

    report_error(DiagnosticCode::ExpectedColon, stream.last_slice(), {.expected = core::token::TokenKind::Colon, .found = stream.peek()});

    return nullptr;
  }

  auto *type_node = parse_type();

  if (!type_node) {
    report_error(DiagnosticCode::ExpectedType, stream.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::Assign, .found = stream.peek()});

    return nullptr;
  }

  core::node::ExpressionNode *value_node = nullptr;

  if (stream.match(core::token::TokenKind::Assign)) {

    value_node = parse_expression();

    if (!value_node) {

      report_error(DiagnosticCode::ExpectedExpression, stream.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::Assign, .found = stream.peek()});

      return nullptr;
    }
  }

  else if (!stream.match(core::token::TokenKind::Semicolon)) {

    report_error(DiagnosticCode::UnexpectedToken, stream.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::Assign, .found = stream.peek()});
    return nullptr;
  }

  return unit.ast.create_node<parser::node::VariableDeclarationNode>(std::move(name), type_node, value_node, mods);
}

int a;
