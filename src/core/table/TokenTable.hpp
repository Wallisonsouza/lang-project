#pragma once

#include "TrieNode.hpp"
#include "core/TransparentHash.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"

#include <deque>
#include <string_view>
#include <unordered_map>

namespace core::table {
class TokenTable {
public:
  token::TokenDescriptor &add(token::TokenKind kind, const std::u32string &name,
                              token::TokenGroup group);
  token::TokenDescriptor &add(token::TokenKind kind, token::TokenGroup group);
  token::TokenDescriptor *lookup_by_kind(token::TokenKind kind);
  token::TokenDescriptor *lookup_by_name(const std::u32string_view &name);

  bool has_prefix(const std::u32string_view &prefix) const {
    return trie_.has_prefix(prefix);
  }

private:
  std::deque<token::TokenDescriptor> storage_;
  std::unordered_map<token::TokenKind, token::TokenDescriptor *> by_kind_;

  std::unordered_map<std::u32string, token::TokenDescriptor *, U32Hash,
                     U32Equal>
      by_name_;

  Trie<token::TokenDescriptor> trie_;
};
} // namespace core::table
