#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_variable_declaration() {

  auto mods = parse_modifiers();

  stream.add_checkpoint();
  auto *name_token = stream.peek();
  if (!name_token ||
      name_token->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  stream.advance();

  core::node::TypeNode *type_node = nullptr;
  if (stream.match(core::token::TokenKind::Colon)) {
    type_node = parse_type();
  }

  core::node::ExpressionNode *value_node = nullptr;
  if (stream.match(core::token::TokenKind::Assign)) {

    value_node = parse_expression();
  }

  auto name = unit.source.buffer.get_text(name_token->slice.span);

  auto *node = unit.ast.create_node<parser::node::VariableDeclarationNode>(
      std::move(name), type_node, value_node, mods);

  stream.discard_checkpoint();

  return node;
}
