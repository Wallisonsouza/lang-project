#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <string>
#include <utility>

struct TokenDescriptor {
  const interpreter::core::TokenKind kind;
  const interpreter::core::TokenGroup group;
  const std::u32string lexeme;

  TokenDescriptor(const std::u32string &lexeme, interpreter::core::TokenKind kind, interpreter::core::TokenGroup group) : lexeme(std::move(lexeme)), kind(kind), group(group) {}
};
