#pragma once
#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/declaration/parse_modifiers.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/statement/match_utils.hpp"

namespace parser::declaration {
inline node::VariableDeclarationNode *parse_variable_declaration(CompilationUnit &unit, core::token::TokenStream &stream) {

  stream.add_checkpoint();

  auto mods = parser::declaration::parse_modifiers(stream);

  auto *name_token = stream.peek();
  if (!name_token || name_token->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  stream.advance();

  if (!expect_token(unit, stream, core::token::TokenKind::Colon)) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  auto *type_node = expect_type(unit, stream);

  core::node::ExpressionNode *value_node = nullptr;
  if (stream.match(core::token::TokenKind::Assign)) { value_node = expect_expression(unit, stream); }

  auto name = unit.source.buffer.get_text(name_token->slice.span);

  auto *node = unit.ast.create_node<node::VariableDeclarationNode>(std::move(name), type_node, value_node, mods);

  stream.match(core::token::TokenKind::Semicolon);
  stream.discard_checkpoint();
  return node;
}

} // namespace parser::declaration
