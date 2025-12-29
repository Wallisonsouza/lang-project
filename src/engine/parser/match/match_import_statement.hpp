#pragma once

#include "core/TokenStream.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

namespace parser::match {

inline node::statement::ImportNode *
match_import_statement(CompilationUnit &unit, TokenStream &stream) {

  stream.push_checkpoint();

  // use
  auto tok = stream.peek();
  if (!tok || tok->descriptor->kind != core::token::TokenKind::UseKeyword) {
    stream.rollback_checkpoint();
    return nullptr;
  }
  stream.advance();

  std::vector<std::u32string> path;

  // primeiro identificador obrigatório
  auto id = stream.peek();
  if (!id || id->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.discard_checkpoint();
    return nullptr;
  }

  while (true) {
    id = stream.peek();
    if (!id || id->descriptor->kind != core::token::TokenKind::Identifier)
      break;

    path.push_back(unit.source.buffer.get_text(id->slice.span));
    stream.advance();

    auto dot = stream.peek();
    if (!dot || dot->descriptor->kind != core::token::TokenKind::Dot)
      break;

    stream.advance();
  }

  stream.discard_checkpoint();

  return unit.ast.create_node<node::statement::ImportNode>(std::move(path));
}

} // namespace parser::match
