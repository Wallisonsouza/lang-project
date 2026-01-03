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
  token::TokenDescriptor &add(token::TokenKind kind, const std::string &name, token::TokenGroup group) {
    storage_.emplace_back(kind, group, name);
    token::TokenDescriptor &desc = storage_.back();
    by_kind_[kind] = &desc;
    by_name_[name] = &desc;
    trie_.insert(name, &desc);
    return desc;
  }

  // Adiciona um token sem nome (ex.: TokenKind::Identifier)
  token::TokenDescriptor &add(token::TokenKind kind, token::TokenGroup group) {
    storage_.emplace_back(kind, group, "");
    token::TokenDescriptor &desc = storage_.back();
    by_kind_[kind] = &desc;
    return desc;
  }

  // Adiciona um alias para um TokenDescriptor existente
  void add_alias(token::TokenKind kind, const std::string &alias) {

    auto desc = lookup_by_kind(kind);
    if (!desc) { return; }

    by_name_[alias] = desc;
    trie_.insert(alias, desc);
    desc->aliases.push_back(alias);
  }

  token::TokenDescriptor *lookup_by_kind(token::TokenKind kind) {
    auto it = by_kind_.find(kind);
    return it != by_kind_.end() ? it->second : nullptr;
  }

  token::TokenDescriptor *lookup_by_name(const std::string_view &name) {
    auto it = by_name_.find(std::string(name));
    return it != by_name_.end() ? it->second : nullptr;
  }

  bool has_prefix(const std::string_view &prefix) const { return trie_.has_prefix(prefix); }

  const std::deque<token::TokenDescriptor> &all() const { return storage_; }

  const std::unordered_map<std::string, token::TokenDescriptor *, U32Hash, U32Equal> &all_names() const { return by_name_; }

  Trie<token::TokenDescriptor> &trie() { return trie_; }

private:
  std::deque<token::TokenDescriptor> storage_;
  std::unordered_map<token::TokenKind, token::TokenDescriptor *> by_kind_;
  std::unordered_map<std::string, token::TokenDescriptor *, U32Hash, U32Equal> by_name_;
  Trie<token::TokenDescriptor> trie_;
};

} // namespace core::table
