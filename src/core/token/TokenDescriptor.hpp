#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <algorithm>
#include <string>
#include <vector>

struct TokenDescriptor {
  const TokenKind kind;
  const TokenGroup group;
  std::u32string primary_name;
  std::vector<std::u32string> aliases;

  bool has_name(const std::u32string &query) const {
    if (query == primary_name)
      return true;
    return std::find(aliases.begin(), aliases.end(), query) != aliases.end();
  }

  void add_alias(const std::u32string &alias) {
    if (std::find(aliases.begin(), aliases.end(), alias) == aliases.end())
      aliases.push_back(alias);
  }
};
