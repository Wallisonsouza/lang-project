
#include "core/token/TokenKind.hpp"
#include "engine/parser/parser.hpp"

#include <cstdint>

inline bool has_flag(RecoverBoundary flags, RecoverBoundary test) {
  return (static_cast<uint32_t>(flags) & static_cast<uint32_t>(test)) != 0;
}

bool is_function_boundary(TokenKind kind) {
  using K = TokenKind;
  return kind == K::FUNCTION_KEYWORD || kind == K::VALUE_KEYWORD ||
         kind == K::IMPORT_KEYWORD;
}

bool is_statement_boundary(TokenKind kind) {
  using K = TokenKind;
  return kind == K::SEMI_COLON || kind == K::NEW_LINE ||
         kind == K::CLOSE_BRACE || kind == K::FUNCTION_KEYWORD ||
         kind == K::VALUE_KEYWORD || kind == K::IMPORT_KEYWORD;
}

bool is_variable_boundary(TokenKind kind) {
  using K = TokenKind;
  return kind == K::SEMI_COLON || kind == K::NEW_LINE ||
         kind == K::CLOSE_BRACE || kind == K::VALUE_KEYWORD ||
         kind == K::FUNCTION_KEYWORD || kind == K::IMPORT_KEYWORD;
}

void Parser::recover_until(RecoverBoundary boundaries) {
  while (!unit.tokens.is_end()) {
    auto *tok = unit.tokens.peek();
    if (!tok || !tok->descriptor) {
      unit.tokens.advance();
      continue;
    }

    auto kind = tok->descriptor->kind;
    bool stop = false;

    if (has_flag(boundaries, RecoverBoundary::Function) &&
        is_function_boundary(kind))
      stop = true;
    if (has_flag(boundaries, RecoverBoundary::Statement) &&
        is_statement_boundary(kind))
      stop = true;
    if (has_flag(boundaries, RecoverBoundary::Variable) &&
        is_variable_boundary(kind))
      stop = true;

    if (stop)
      return;

    unit.tokens.advance();
  }
}