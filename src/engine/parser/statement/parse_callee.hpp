#pragma once

#include "core/node/Type.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement_nodes.hpp"

namespace parser::match {

inline core::node::ExpressionNode *parse_callee(CompilationUnit &unit, core::token::TokenStream &stream) {
  auto tok = stream.peek();
  if (!tok || tok->descriptor->kind != core::token::TokenKind::Identifier) { return nullptr; }

  tok = stream.consume();
  core::node::ExpressionNode *expr = unit.ast.create_node<node::IdentifierNode>(unit.source.buffer.get_text(tok->slice.span));

  while (true) {
    auto dot = stream.peek();
    if (!dot || dot->descriptor->kind != core::token::TokenKind::Dot) break;

    stream.advance();

    auto prop_tok = stream.peek();
    if (!prop_tok || prop_tok->descriptor->kind != core::token::TokenKind::Identifier) return nullptr;

    prop_tok = stream.consume();
    auto prop_expr = unit.ast.create_node<node::IdentifierNode>(unit.source.buffer.get_text(prop_tok->slice.span));

    expr = unit.ast.create_node<node::MemberAccessNode>(expr, prop_expr);
  }

  return expr;
}

} // namespace parser::match
