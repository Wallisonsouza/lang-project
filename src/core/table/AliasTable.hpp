#pragma once

#include "TrieNode.hpp"
#include "core/token/TokenDescriptor.hpp"
#include <string>
#include <unordered_map>

class AliasTable {
public:
  void add_alias(const std::u32string &alias, TokenDescriptor *descriptor);

  bool has_prefix(const std::u32string &prefix) const;
  TokenDescriptor *lookup_by_name(const std::u32string &alias) const;
  bool has_alias(const std::u32string &alias) const;

  void clear();

private:
  std::unordered_map<std::u32string, TokenDescriptor *> by_name_;
  TokenTrie trie_;
};
