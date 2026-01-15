#include "engine/parser/parser.hpp"
#include "core/token/TokenKind.hpp"

void Parser::synchronize_statement() {
  while (!unit.tokens.is_end()) {
    auto kind = unit.tokens.peek()->descriptor->kind;

    if (kind == core::token::TokenKind::Newline || kind == core::token::TokenKind::CloseBrace) {
      unit.tokens.advance();
      return;
    }

    unit.tokens.advance();
  }
}

void Parser::synchronize_parameter() {
  while (!unit.tokens.is_end()) {
    auto kind = unit.tokens.peek()->descriptor->kind;
    if (kind == core::token::TokenKind::Comma || kind == core::token::TokenKind::CloseParen) { return; }
    unit.tokens.advance();
  }
}
