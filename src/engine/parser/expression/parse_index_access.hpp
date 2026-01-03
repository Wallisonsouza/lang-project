#pragma once
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "parse_expression.hpp"

namespace parser::expression {

inline core::node::ExpressionNode *
parse_index_access(CompilationUnit &unit, core::token::TokenStream &stream,
                   core::node::ExpressionNode *base) {
  if (!base)
    return nullptr;

  while (true) {
    auto *tok = stream.peek();
    if (!tok || tok->descriptor->kind != core::token::TokenKind::OpenBracket)
      break;
    stream.advance();

    auto *index = parse_expression(unit, stream);
    if (!index || !stream.match(core::token::TokenKind::CloseBracket))
      break;

    base =
        unit.ast.create_node<node::parser::node::IndexAccessNode>(base, index);
  }

  return base;
}

} // namespace parser::expression
