#pragma once

#include "TrieNode.hpp"
#include "core/TransparentHash.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenKind.hpp"
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace interpreter::core {

class AliasTable {
public:
  void add(const std::u32string &alias, TokenDescriptor *descriptor);

  bool has_prefix(const std::u32string_view &prefix) const;

  TokenDescriptor *lookup_by_name(const std::u32string_view &alias) const;

  bool has_alias(const std::u32string_view &alias) const;

  const std::vector<std::u32string_view> &get_aliases(const TokenDescriptor *descriptor) const;

  const std::vector<std::u32string_view> &get_aliases(TokenKind kind) const;

  void clear();

private:
  std::unordered_map<std::u32string_view, TokenDescriptor *, U32Hash, U32Equal> by_name_;

  std::unordered_map<TokenKind, std::vector<std::u32string_view>> by_kind_;

  Trie<TokenDescriptor> trie_;
};

} // namespace interpreter::core
