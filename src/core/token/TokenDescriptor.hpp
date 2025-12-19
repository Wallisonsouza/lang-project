#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <string>
#include <utility>

namespace core::token {
struct TokenDescriptor {
  const TokenKind kind;
  const TokenGroup group;
  const std::u32string lexeme;

  TokenDescriptor(const std::u32string &lexeme, TokenKind kind, TokenGroup group) : lexeme(std::move(lexeme)), kind(kind), group(group) {}
};
} // namespace core::token
