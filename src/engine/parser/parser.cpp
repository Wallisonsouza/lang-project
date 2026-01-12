#include "engine/parser/parser.hpp"
#include "core/token/TokenKind.hpp"

void Parser::synchronize_statement() {
  while (!unit.tokens.is_end()) {
    auto current = unit.tokens.peek();
    if (!current) {
      unit.tokens.advance();
      continue;
    }

    auto kind = current->descriptor->kind;

    switch (kind) {
    case core::token::TokenKind::Semicolon:
    case core::token::TokenKind::CloseBrace:
    case core::token::TokenKind::IfKeyword:
    case core::token::TokenKind::ValueKeyword:
    case core::token::TokenKind::WhileKeyword:
    case core::token::TokenKind::ForKeyword:
    case core::token::TokenKind::ReturnKeyword: return;

    default: unit.tokens.advance();
    }
  }
}

void Parser::synchronize_parameter() {
  while (!unit.tokens.is_end()) {
    if (unit.tokens.peek(core::token::TokenKind::Comma) || unit.tokens.peek(core::token::TokenKind::CloseParen)) { return; }
    unit.tokens.advance();
  }
}
