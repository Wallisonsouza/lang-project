#pragma once
#include "core/token/TokenDescriptor.hpp"
#include <string>

namespace lang::core {

struct Location {
  size_t line;
  size_t start;
  size_t end;
};

struct Token {
  const TokenDescriptor *descriptor;
  const Location location;
  const std::u32string lexeme;

  Token(const TokenDescriptor *desc, std::u32string lex, const Location &loc) : descriptor(desc), location(loc), lexeme(std::move(lex)) {}
};

} // namespace lang::core
