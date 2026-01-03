#pragma once
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "parse_expression.hpp"

namespace parser::expression {

inline core::node::ExpressionNode *
parse_function_expression(CompilationUnit &unit,
                          core::token::TokenStream &stream,
                          core::node::ExpressionNode *base) {
  if (!base)
    return nullptr;

  while (true) {
    auto *tok = stream.peek();
    if (!tok || tok->descriptor->kind != core::token::TokenKind::OpenParen)
      break;
    stream.advance(); // consumir '('

    std::vector<core::node::ExpressionNode *> args;
    while (!stream.is_end() &&
           !stream.match(core::token::TokenKind::CloseParen)) {
      auto *expr = parse_expression(unit, stream);
      if (!expr)
        break;
      args.push_back(expr);

      if (!stream.match(core::token::TokenKind::Comma)) {
        stream.match(core::token::TokenKind::CloseParen);
        break;
      }
    }

    base = unit.ast.create_node<node::FunctionCallNode>(base, args);
  }

  return base;
}

} // namespace parser::expression
