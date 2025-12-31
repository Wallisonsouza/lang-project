#pragma once

#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/ExpressionParser.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

namespace parser::match {

inline node::statement::ImportNode *match_import_statement(CompilationUnit &unit, core::token::TokenStream &stream, ExpressionParser &exp) {
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

  const node::IdentifierNode *alias_node = nullptr;
  auto as_tok = stream.peek();
  if (as_tok && as_tok->descriptor->kind == core::token::TokenKind::AsKeyword) {
    stream.advance();
    auto expr = exp.parse_expression(unit, stream);
    if (expr && expr->kind == core::node::NodeKind::Identifier) { alias_node = static_cast<const node::IdentifierNode *>(expr); }
  }

  stream.discard_checkpoint();

  auto node = unit.ast.create_node<node::statement::ImportNode>(std::move(path));
  node->alias = alias_node;

  return node;
}

} // namespace parser::match
