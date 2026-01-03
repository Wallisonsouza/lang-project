#pragma once
#include "parse_expression.hpp"
#include "parse_binary_expression.hpp"
#include "parse_postfix_expression.hpp"

namespace parser::expression {

core::node::ExpressionNode *parse_expression(CompilationUnit &unit,
                                             core::token::TokenStream &stream) {

  auto *primary = parse_postfix_expression(unit, stream);

  if (!primary) {
    return nullptr;
  }

  if (auto bin = parse_binary_expression(unit, stream, 0, primary)) {
    return bin;
  }

  return nullptr;
}

} // namespace parser::expression
