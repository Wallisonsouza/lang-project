#pragma once
#include "core/TokenStream.hpp"
#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/ExpressionParser.hpp"
#include "engine/parser/match/match_modifier.hpp"
#include "engine/parser/match/match_type.hpp"
#include "engine/parser/node/statement_nodes.hpp"

namespace parser::match {

inline node::VariableDeclarationNode *
match_variable_declaration(CompilationUnit &unit, TokenStream &stream,
                           ExpressionParser &exp) {
  stream.push_checkpoint();
  bool has_error = false;

  auto mod = match::match_modifier(stream);

  if (!core::node::hasModifier(mod, core::node::Modifier::Mut) &&
      !core::node::hasModifier(mod, core::node::Modifier::Value)) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  // 1. Nome da variável
  auto name_token = stream.peek();
  if (!name_token ||
      name_token->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.rollback_checkpoint();
    return nullptr;
  }
  stream.advance();

  // 2. Dois-pontos obrigatórios
  auto colon_token = stream.peek();
  if (!colon_token ||
      colon_token->descriptor->kind != core::token::TokenKind::Colon) {
    stream.rollback_checkpoint();

    return nullptr;
  }
  stream.advance();

  // 3. Tipo
  core::node::TypeNode *type_node = match_type(unit, stream);
  if (!type_node) {
    type_node = unit.ast.create_node<core::node::TypeNode>(U"<missing>", false);
    type_node->has_error = true;
    has_error = true;
  }

  // 4. Valor opcional
  core::node::ExpressionNode *value_node = nullptr;
  auto assign_token = stream.peek();
  if (assign_token &&
      assign_token->descriptor->kind == core::token::TokenKind::Assign) {
    stream.advance();
    value_node = exp.parse_expression(unit, stream);
  }

  if (!value_node) {
    value_node = unit.ast.create_node<node::IdentifierNode>(U"<missing>");
    value_node->has_error = true;
    has_error = true;
  }

  auto node = unit.ast.create_node<node::VariableDeclarationNode>(
      unit.source.buffer.get_text(name_token->span), type_node, value_node,
      mod);
  node->has_error = has_error;

  auto semicolon_token = stream.peek();
  if (semicolon_token &&
      semicolon_token->descriptor->kind == core::token::TokenKind::Semicolon) {
    stream.advance();
  }

  stream.discard_checkpoint();
  return node;
}

} // namespace parser::match
