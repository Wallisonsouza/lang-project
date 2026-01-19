#include "engine/parser/parser.hpp"

void Parser::recover_until(BoundaryFn boundary) {
  while (!unit.tokens.is_end()) {
    auto *tok = unit.tokens.peek();

    if (!tok || !tok->descriptor) {
      unit.tokens.advance();
      continue;
    }

    auto kind = tok->descriptor->kind;

    if (boundary(kind)) {
      return;
    }

    unit.tokens.advance();
  }
}

bool is_statement_boundary(core::token::TokenKind kind) {
  using K = core::token::TokenKind;

  return kind == K::Semicolon || kind == K::CLOSE_BRACE ||
         kind == K::FUNCTION_KEYWORD || kind == K::VALUE_KEYWORD ||
         kind == K::IMPORT_KEYWORD;
}

bool is_function_boundary(core::token::TokenKind kind) {
  using K = core::token::TokenKind;

  return kind == K::FUNCTION_KEYWORD || kind == K::VALUE_KEYWORD ||
         kind == K::IMPORT_KEYWORD;
}

void Parser::synchronize_statement() { recover_until(is_statement_boundary); }

void Parser::synchronize_function() { recover_until(is_function_boundary); }
