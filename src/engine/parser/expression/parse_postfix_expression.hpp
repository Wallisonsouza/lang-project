#pragma once

#include "engine/parser/expression/parse_function_expression.hpp"
#include "engine/parser/expression/parse_index_access.hpp"
#include "engine/parser/expression/parse_member_access.hpp"
#include "parse_primary_expression.hpp"

namespace parser::expression {
inline core::node::ExpressionNode *
parse_postfix_expression(CompilationUnit &unit,
                         core::token::TokenStream &stream) {

  auto *expr = parse_primary_expression(unit, stream);
  if (!expr)
    return nullptr;

  while (true) {
    auto *tok = stream.peek();
    if (!tok)
      break;

    switch (tok->descriptor->kind) {

    case core::token::TokenKind::OpenParen:
      expr = parse_function_expression(unit, stream, expr);
      break;

    case core::token::TokenKind::Dot:
      expr = parse_member_access(unit, stream, expr);
      break;

    case core::token::TokenKind::OpenBracket:
      expr = parse_index_access(unit, stream, expr);
      break;

    default:
      return expr;
    }
  }

  return expr;
}

} // namespace parser::expression
