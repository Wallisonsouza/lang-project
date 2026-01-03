#pragma once
#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include <iostream>

namespace parser::expression {

inline core::node::ExpressionNode *
parse_path(CompilationUnit &unit, core::token::TokenStream &stream) {
  stream.add_checkpoint();

  auto id_tok = stream.peek();
  std::cout << "pass";
  if (!id_tok ||
      id_tok->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  std::vector<parser::node::IdentifierNode *> segments;

  while (true) {
    auto id_tok = stream.peek();
    if (!id_tok ||
        id_tok->descriptor->kind != core::token::TokenKind::Identifier)
      break;

    auto *id_node = unit.ast.create_node<parser::node::IdentifierNode>(
        unit.source.buffer.get_text(id_tok->slice.span));
    segments.push_back(id_node);

    stream.advance();

    auto sep_tok = stream.peek();
    if (!sep_tok ||
        sep_tok->descriptor->kind != core::token::TokenKind::DoubleColon)
      break;

    stream.advance();
  }

  stream.discard_checkpoint();

  if (segments.empty())
    return nullptr;

  return unit.ast.create_node<parser::node::statement::PathExprNode>(
      std::move(segments));
}

} // namespace parser::expression
