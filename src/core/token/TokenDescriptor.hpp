#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <string>

struct TokenDescriptor {
  const lang::core::TokenKind kind;
  const lang::core::TokenGroup group;
  std::u32string lexeme;
};
