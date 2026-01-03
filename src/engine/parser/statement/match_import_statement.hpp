#pragma once

#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include <string>
#include <vector>

namespace parser::statement {

inline node::statement::ImportNode *
match_import_statement(CompilationUnit &unit,
                       core::token::TokenStream &stream) {
  auto use_tok = stream.peek();
  if (!use_tok ||
      use_tok->descriptor->kind != core::token::TokenKind::UseKeyword)
    return nullptr;

  stream.advance();

  std::vector<parser::node::IdentifierNode *> path_nodes;

  while (true) {
    auto id_tok = stream.peek();
    if (!id_tok ||
        id_tok->descriptor->kind != core::token::TokenKind::Identifier)
      break;

    // Cria um IdentifierNode para cada identificador do path
    auto *id_node = unit.ast.create_node<parser::node::IdentifierNode>(
        unit.source.buffer.get_text(id_tok->slice.span));
    path_nodes.push_back(id_node);

    stream.advance();

    auto sep_tok = stream.peek();
    if (!sep_tok ||
        sep_tok->descriptor->kind != core::token::TokenKind::DoubleColon)
      break;

    stream.advance();
  }

  if (path_nodes.empty())
    return nullptr;

  std::optional<std::string> alias;
  auto as_tok = stream.peek();
  if (as_tok && as_tok->descriptor->kind == core::token::TokenKind::AsKeyword) {
    stream.advance();
    auto id_tok = stream.peek();
    if (!id_tok ||
        id_tok->descriptor->kind != core::token::TokenKind::Identifier)
      return nullptr;

    alias = unit.source.buffer.get_text(id_tok->slice.span);
    stream.advance();
  }

  auto *node =
      unit.ast.create_node<node::statement::ImportNode>(std::move(path_nodes));
  node->alias = std::move(alias);
  node->slice = stream.last_slice();
  return node;
}

} // namespace parser::statement
