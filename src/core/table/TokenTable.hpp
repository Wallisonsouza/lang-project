#pragma once

#include "TrieNode.hpp"
#include "core/TransparentHash.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"

#include <deque>
#include <string_view>
#include <unordered_map>

class TokenTable {
public:
  TokenDescriptor &add(interpreter::core::TokenKind kind, const std::u32string &name, interpreter::core::TokenGroup group);
  TokenDescriptor &add(interpreter::core::TokenKind kind, interpreter::core::TokenGroup group);
  TokenDescriptor *lookup_by_kind(interpreter::core::TokenKind kind);
  TokenDescriptor *lookup_by_name(const std::u32string_view &name);

  bool has_prefix(const std::u32string_view &prefix) const { return trie_.has_prefix(prefix); }

private:
  std::deque<TokenDescriptor> storage_;
  std::unordered_map<interpreter::core::TokenKind, TokenDescriptor *> by_kind_;


  std::unordered_map<std::u32string, TokenDescriptor *, U32Hash, U32Equal> by_name_;



  
  Trie<TokenDescriptor> trie_;
};
