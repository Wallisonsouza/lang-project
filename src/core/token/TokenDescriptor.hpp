#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <string>
#include <vector>

namespace core::token {

struct TokenDescriptor {

  const TokenKind kind;
  const TokenGroup group;
  const std::string name;
  std::vector<std::string> aliases;

  TokenDescriptor(TokenKind kind, TokenGroup group, const std::string &lexeme) : kind(kind), group(group), name(lexeme) {}
};
} // namespace core::token
