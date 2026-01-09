#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_path_expression() {
  unit.tokens.add_checkpoint();

  auto id_tok = unit.tokens.peek();

  if (!id_tok || id_tok->descriptor->kind != core::token::TokenKind::Identifier) {
    unit.tokens.rollback_checkpoint();
    return nullptr;
  }

  std::vector<core::node::IdentifierNode *> segments;

  while (true) {
    auto id_tok = unit.tokens.peek();
    if (!id_tok || id_tok->descriptor->kind != core::token::TokenKind::Identifier) break;

    auto *id_node = unit.ast.create_node<core::node::IdentifierNode>(unit.source.buffer.get_text(id_tok->slice.span));
    segments.push_back(id_node);

    unit.tokens.advance();

    auto sep_tok = unit.tokens.peek();
    if (!sep_tok || sep_tok->descriptor->kind != core::token::TokenKind::Dot) break;

    unit.tokens.advance();
  }

  unit.tokens.discard_checkpoint();

  if (segments.empty()) return nullptr;

  return unit.ast.create_node<parser::node::statement::PathExprNode>(std::move(segments));
}
