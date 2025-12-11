#include "TokenTable.hpp"
#include <string_view>

TokenDescriptor &TokenTable::add(interpreter::core::TokenKind kind, const std::u32string &name, interpreter::core::TokenGroup group) {
  storage_.push_back(TokenDescriptor(name, kind, group));
  TokenDescriptor *ptr = &storage_.back();

  by_kind_[kind] = ptr;
  by_name_[name] = ptr;
  trie_.insert(name, ptr);

  return *ptr;
}

TokenDescriptor &TokenTable::add(interpreter::core::TokenKind kind, interpreter::core::TokenGroup group) {
  storage_.emplace_back(U"", kind, group);
  TokenDescriptor *ptr = &storage_.back();

  by_kind_[kind] = ptr;

  return *ptr;
}
TokenDescriptor *TokenTable::lookup_by_kind(interpreter::core::TokenKind kind) {
  auto it = by_kind_.find(kind);
  return it != by_kind_.end() ? it->second : nullptr;
}

TokenDescriptor *TokenTable::lookup_by_name(const std::u32string_view &name) {
  auto it = by_name_.find(name);
  return it != by_name_.end() ? it->second : nullptr;
}
