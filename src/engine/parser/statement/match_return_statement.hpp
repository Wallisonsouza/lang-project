#pragma once

#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"

#include "engine/CompilationUnit.hpp"
#include "engine/parser/ExpressionParser.hpp"
#include "engine/parser/node/statement_nodes.hpp"

namespace parser::match {

inline node::ReturnStatementNode *match_return_statement(CompilationUnit &unit, core::token::TokenStream &stream, ExpressionParser &exp) {

  auto tok = stream.peek();
  if (!tok || tok->descriptor->kind != core::token::TokenKind::ReturnKeyword) { return nullptr; }

  stream.advance();

  auto value = exp.parse_expression(unit, stream);

  return unit.ast.create_node<node::ReturnStatementNode>(value);
}

} // namespace parser::match
