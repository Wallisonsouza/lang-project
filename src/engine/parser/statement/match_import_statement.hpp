#pragma once

#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

namespace parser::statement {

inline node::statement::ImportNode *match_import_statement(CompilationUnit &unit, core::token::TokenStream &stream) {
  stream.add_checkpoint();

  auto tok = stream.peek();
  if (!tok || tok->descriptor->kind != core::token::TokenKind::UseKeyword) {
    stream.rollback_checkpoint();
    return nullptr;
  }
  stream.advance();

  std::vector<std::u32string> path;

  while (true) {
    auto id_tok = stream.peek();
    if (!id_tok || id_tok->descriptor->kind != core::token::TokenKind::Identifier) break;

    path.push_back(unit.source.buffer.get_text(id_tok->slice.span));
    stream.advance();

    auto dot_tok = stream.peek();
    if (!dot_tok || dot_tok->descriptor->kind != core::token::TokenKind::Dot) break;

    stream.advance();
  }

  if (path.empty()) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  std::optional<std::u32string> alias;

  auto as_tok = stream.peek();
  if (as_tok && as_tok->descriptor->kind == core::token::TokenKind::AsKeyword) {
    stream.advance();

    auto id_tok = stream.peek();
    if (!id_tok || id_tok->descriptor->kind != core::token::TokenKind::Identifier) {
      stream.rollback_checkpoint();
      return nullptr;
    }

    alias = unit.source.buffer.get_text(id_tok->slice.span);
    stream.advance();
  }

  stream.discard_checkpoint();

  auto *node = unit.ast.create_node<node::statement::ImportNode>(std::move(path));
  node->alias = std::move(alias);
  node->slice = stream.last_slice();

  return node;
}

} // namespace parser::statement
