#pragma once

#include "core/node/Type.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/match/match_utils.hpp"
#include "engine/parser/match/parse_callee.hpp"
#include "engine/parser/node/statement_nodes.hpp"

#include <vector>

namespace parser::match {

inline node::FunctionCallNode *match_function_call(CompilationUnit &unit, core::token::TokenStream &stream) {

  auto callee_expr = parser::match::parse_callee(unit, stream);
  if (!callee_expr) return nullptr;

  // Espera '('
  if (!expect_token(unit, stream, core::token::TokenKind::OpenParen, "Expected '(' for function call")) return nullptr;

  std::vector<core::node::ExpressionNode *> args;

  while (!stream.is_end()) {
    auto arg = exp.parse_expression(unit, stream);
    if (!arg) break;

    args.push_back(arg);

    auto comma = stream.peek();
    if (comma && comma->descriptor->kind == core::token::TokenKind::Comma)
      stream.advance();
    else
      break;
  }

  if (!expect_token(unit, stream, core::token::TokenKind::CloseParen, "Expected ')' after arguments")) return nullptr;

  return unit.ast.create_node<node::FunctionCallNode>(callee_expr, args);
}

} // namespace parser::match
