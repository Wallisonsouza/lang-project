#pragma once

#include "core/CompilationUnit.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "parser/ExpressionParser.hpp"
#include "parser/match/match_block.hpp"
#include "parser/match/match_function_parameter.hpp"
#include "parser/match/match_modifier.hpp"
#include "parser/match/match_type.hpp"
#include "parser/match/match_utils.hpp"
#include "parser/node/type_nodes.hpp"
#include "utils/Stream.hpp"
#include <vector>

namespace parser::match {

inline node::FunctionDeclarationNode *match_function_declaration(CompilationUnit &unit, utils::Stream<core::token::Token *> &stream, ExpressionParser &exp) {

  auto mod = match_modifier(stream);

  stream.push_checkpoint();
  bool has_error = false;

  auto keyword = stream.peek();
  if (!keyword || keyword->descriptor->kind != core::token::TokenKind::FunctionKeyword) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  stream.advance();

  // 1. Nome da função
  auto name_token = stream.peek();
  if (!name_token || name_token->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.rollback_checkpoint();
    return nullptr;
  }
  stream.advance();

  // 4. Parâmetros entre parênteses
  std::vector<node::FunctionParameterNode *> parameters;
  if (!expect_token(unit, stream, core::token::TokenKind::OpenParen, "Expected '(' for function parameters")) {
    has_error = true;
  } else {
    while (!stream.is_end()) {
      auto param = match_function_parameter(unit, stream, exp);
      if (!param) break;
      parameters.push_back(param);

      auto comma = stream.peek();
      if (comma && comma->descriptor->kind == core::token::TokenKind::Comma) {
        stream.advance();
      } else {
        break;
      }
    }

    if (!expect_token(unit, stream, core::token::TokenKind::CloseParen, "Expected ')' after parameters")) { has_error = true; }
  }

  // 5. Tipo de retorno opcional
  node::TypeNode *return_type = nullptr;
  auto next = stream.peek();
  if (next && next->descriptor->kind == core::token::TokenKind::Arrow) {
    stream.advance();
    return_type = match_type(unit, stream);
    if (!return_type) {
      return_type = unit.ast.create_node<node::TypeNode>(U"<missing>", false);
      return_type->has_error = true;
      has_error = true;
    }
  } else {
    return_type = unit.ast.create_node<node::TypeNode>(U"void", false);
  }

  // 6. Bloco da função
  node::BlockNode *body;
  if (!body) has_error = true;

  // 7. Criar o nó final
  auto node = unit.ast.create_node<node::FunctionDeclarationNode>(unit.source.buffer.get_text(name_token->span), parameters, return_type, body, mod);
  node->has_error = has_error;

  stream.discard_checkpoint();
  return node;
}

} // namespace parser::match
