#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/parser.hpp"

core::node::ExpressionNode *Parser::parse_primary_expression() {

  auto *tok = unit.tokens.peek();
  if (!tok) return nullptr;

  core::node::ExpressionNode *result = nullptr;

  switch (tok->descriptor->kind) {

  case core::token::TokenKind::NumberLiteral: {
    result = unit.ast.create_node<parser::node::NumberLiteralNode>(std::stod(unit.source.buffer.get_text(tok->slice.span)));
    unit.tokens.advance();
    break;
  }

  case core::token::TokenKind::StringLiteral: {
    result = unit.ast.create_node<parser::node::StringLiteralNode>(unit.source.buffer.get_text(tok->slice.span));
    unit.tokens.advance();
    break;
  }

  case core::token::TokenKind::Identifier: {
    auto *next = unit.tokens.peek(1);
    if (next && next->descriptor->kind == core::token::TokenKind::DoubleColon) {
      result = parse_path_expression();
    } else {
      result = unit.ast.create_node<parser::node::IdentifierNode>(unit.source.buffer.get_text(tok->slice.span));
      result->slice = tok->slice;
      unit.tokens.advance();
    }
    break;
  }

  case core::token::TokenKind::OpenParen: {
    unit.tokens.advance();
    result = parse_expression();
    auto *close = unit.tokens.consume();
    if (!result || !close || close->descriptor->kind != core::token::TokenKind::CloseParen) return nullptr;
    break;
  }

  default: return nullptr;
  }

  return result;
}