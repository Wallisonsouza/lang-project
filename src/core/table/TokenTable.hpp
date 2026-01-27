#pragma once
#include "TrieNode.hpp"
#include "core/hash/TransparentHash.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <deque>
#include <string>
#include <unordered_map>

namespace core::table {

class DescriptorTable {
public:
  TokenDescriptor &add(TokenKind kind, const std::string &name,
                       TokenGroup group) {
    storage_.emplace_back(kind, group, name);
    TokenDescriptor &desc = storage_.back();
    by_kind_[kind] = &desc;
    by_name_[name] = &desc;
    trie_.insert(name, &desc);
    return desc;
  }

  // Adiciona um token sem nome (ex.: TokenKind::Identifier)
  TokenDescriptor &add(TokenKind kind, TokenGroup group) {
    storage_.emplace_back(kind, group, "");
    TokenDescriptor &desc = storage_.back();
    by_kind_[kind] = &desc;
    return desc;
  }

  // Adiciona um alias para um TokenDescriptor existente
  void add_alias(TokenKind kind, const std::string &alias) {

    auto desc = lookup_by_kind(kind);
    if (!desc) {
      return;
    }

    by_name_[alias] = desc;
    trie_.insert(alias, desc);
    desc->aliases.push_back(alias);
  }

  TokenDescriptor *lookup_by_kind(TokenKind kind) {
    auto it = by_kind_.find(kind);
    return it != by_kind_.end() ? it->second : nullptr;
  }

  TokenDescriptor *lookup_by_name(const std::string_view &name) {
    auto it = by_name_.find(std::string(name));
    return it != by_name_.end() ? it->second : nullptr;
  }

  bool has_prefix(const std::string_view &prefix) const {
    return trie_.has_prefix(prefix);
  }

  const std::deque<TokenDescriptor> &all() const { return storage_; }

  const std::unordered_map<std::string, TokenDescriptor *, U32Hash, U32Equal> &
  all_names() const {
    return by_name_;
  }

  Trie<TokenDescriptor> &trie() { return trie_; }

private:
  std::deque<TokenDescriptor> storage_;
  std::unordered_map<TokenKind, TokenDescriptor *> by_kind_;
  std::unordered_map<std::string, TokenDescriptor *, U32Hash, U32Equal>
      by_name_;
  Trie<TokenDescriptor> trie_;
};

} // namespace core::table
