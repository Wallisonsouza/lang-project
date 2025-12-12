#pragma once

#include "TrieNode.hpp"
#include "core/TransparentHash.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenKind.hpp"
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace core::table {

class AliasTable {
public:
  void add(const std::u32string &alias, token::TokenDescriptor *descriptor);

  bool has_prefix(const std::u32string_view &prefix) const;

  token::TokenDescriptor *
  lookup_by_name(const std::u32string_view &alias) const;

  bool has_alias(const std::u32string_view &alias) const;

  const std::vector<std::u32string_view> &
  get_aliases(const token::TokenDescriptor *descriptor) const;

  const std::vector<std::u32string_view> &
  get_aliases(token::TokenKind kind) const;

  void clear();

private:
  std::unordered_map<std::u32string_view, token::TokenDescriptor *, U32Hash,
                     U32Equal>
      by_name_;

  std::unordered_map<token::TokenKind, std::vector<std::u32string_view>>
      by_kind_;

  Trie<token::TokenDescriptor> trie_;
};

} // namespace core::table
