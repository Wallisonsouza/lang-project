#pragma once

#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/expression/expression.hpp"
#include "engine/parser/match/match_type.hpp"
#include "engine/parser/node/literal_nodes.hpp"

namespace parser::match {

inline core::node::FunctionParameterNode *match_function_parameter(CompilationUnit &unit, core::token::TokenStream &stream) {
  stream.add_checkpoint();

  // 1. Nome da variável
  auto name_token = stream.peek();
  if (!name_token || name_token->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  stream.advance();

  // 2. Dois-pontos obrigatórios
  auto colon_token = stream.peek();
  if (!colon_token || colon_token->descriptor->kind != core::token::TokenKind::Colon) {
    stream.rollback_checkpoint();

    return nullptr;
  }
  stream.advance();

  // 3. Tipo
  core::node::TypeNode *type_node = parse_type(unit, stream);
  if (!type_node) { type_node = unit.ast.create_node<core::node::TypeNode>(U"<missing>", false); }

  // 4. Valor opcional
  core::node::ExpressionNode *value_node = nullptr;
  auto assign_token = stream.peek();
  if (assign_token && assign_token->descriptor->kind == core::token::TokenKind::Assign) {
    stream.advance();
    value_node = parser::expression::parse_expression(unit, stream);
  }

  if (!value_node) { value_node = unit.ast.create_node<node::IdentifierNode>(U"<missing>"); }

  auto node = unit.ast.create_node<core::node::FunctionParameterNode>(unit.source.buffer.get_text(name_token->slice.span), type_node, value_node);

  auto semicolon_token = stream.peek();
  if (semicolon_token && semicolon_token->descriptor->kind == core::token::TokenKind::Semicolon) { stream.advance(); }

  stream.discard_checkpoint();
  return node;
}

} // namespace parser::match
