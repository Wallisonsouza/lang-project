#include "engine/parser/parser.hpp"

void Parser::synchronize_statement() {
  while (!unit.tokens.is_end()) {
    auto current = unit.tokens.peek();
    if (!current) {
      unit.tokens.advance();
      continue;
    }

    auto kind = current->descriptor->kind;
    auto group = current->descriptor->group;

    if (group == core::token::TokenGroup::Keyword || kind == core::token::TokenKind::Semicolon || kind == core::token::TokenKind::CloseBrace) { return; }

    unit.tokens.advance();
  }
}