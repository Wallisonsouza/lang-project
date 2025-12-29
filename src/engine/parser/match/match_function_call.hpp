#pragma once

#include "core/TokenStream.hpp"
#include "core/node/Type.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/ExpressionParser.hpp"
#include "engine/parser/match/match_utils.hpp"
#include "engine/parser/node/statement_nodes.hpp"

#include <vector>

namespace parser::match {

inline node::FunctionCallNode *match_function_call(CompilationUnit &unit,
                                                   TokenStream &stream,
                                                   ExpressionParser &exp) {

  // Primeiro pega o identificador da função
  auto tok = stream.consume();
  if (!tok || tok->descriptor->kind != core::token::TokenKind::Identifier)
    return nullptr;

  auto callee_expr = unit.ast.create_node<node::IdentifierNode>(
      unit.source.buffer.get_text(tok->slice.span));

  // Espera '('
  if (!expect_token(unit, stream, core::token::TokenKind::OpenParen,
                    "Expected '(' for function call"))
    return nullptr;

  std::vector<core::node::ExpressionNode *> args;

  while (!stream.is_end()) {
    // parse_expression já lida com parênteses internos
    auto arg = exp.parse_expression(unit, stream);
    if (!arg)
      break;

    args.push_back(arg);

    auto comma = stream.peek();
    if (comma && comma->descriptor->kind == core::token::TokenKind::Comma)
      stream.advance();
    else
      break;
  }

  // Espera ')'
  if (!expect_token(unit, stream, core::token::TokenKind::CloseParen,
                    "Expected ')' after arguments"))
    return nullptr;

  return unit.ast.create_node<node::FunctionCallNode>(callee_expr, args);
}

} // namespace parser::match
