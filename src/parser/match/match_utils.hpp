#pragma once
#include "core/CompilationUnit.hpp"
#include "utils/Stream.hpp"

inline bool expect_token(CompilationUnit &unit, utils::Stream<core::token::Token *> &stream, core::token::TokenKind kind, const std::string &message) {
  auto tok = stream.peek();
  if (!tok || tok->descriptor->kind != kind) return false;
  stream.advance();
  return true;
}
