#pragma once

#include "TrieNode.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"

#include <deque>
#include <unordered_map>

class TokenTable {
public:
  TokenDescriptor &add_token(lang::core::TokenKind kind, const std::u32string &name, lang::core::TokenGroup group);

  TokenDescriptor *lookup_by_kind(lang::core::TokenKind kind);
  TokenDescriptor *lookup_by_name(const std::u32string &name);

  bool has_prefix(const std::u32string &prefix) const { return trie_.has_prefix(prefix); }

private:
  std::deque<TokenDescriptor> storage_;
  std::unordered_map<lang::core::TokenKind, TokenDescriptor *> by_kind_;
  std::unordered_map<std::u32string, TokenDescriptor *> by_name_;
  TokenTrie trie_;
};
