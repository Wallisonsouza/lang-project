#pragma once
#include "core/CompilationUnit.hpp"
#include "core/TokenStream.hpp"

inline bool expect_token(CompilationUnit &unit, TokenStream &stream, core::token::TokenKind kind, const std::string &message) {
  auto tok = stream.peek();
  if (!tok || tok->descriptor->kind != kind) return false;
  stream.advance();
  return true;
}
