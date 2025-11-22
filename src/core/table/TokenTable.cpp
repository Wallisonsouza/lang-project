#include "TokenTable.hpp"

TokenDescriptor &TokenTable::add_token(lang::core::TokenKind kind, const std::u32string &name, lang::core::TokenGroup group) {
  storage_.push_back(TokenDescriptor{kind, group, name});
  TokenDescriptor *ptr = &storage_.back();

  by_kind_[kind] = ptr;
  by_name_[name] = ptr;
  trie_.insert(name, ptr);

  return *ptr;
}

TokenDescriptor *TokenTable::lookup_by_kind(lang::core::TokenKind kind) {
  auto it = by_kind_.find(kind);
  return it != by_kind_.end() ? it->second : nullptr;
}

TokenDescriptor *TokenTable::lookup_by_name(const std::u32string &name) {
  auto it = by_name_.find(name);
  return it != by_name_.end() ? it->second : nullptr;
}