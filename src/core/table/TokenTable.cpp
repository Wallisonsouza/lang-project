#include "TokenTable.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include <string_view>

namespace core::table {
token::TokenDescriptor &DescriptorTable::add(token::TokenKind kind,
                                             const std::u32string &name,
                                             token::TokenGroup group) {
  storage_.push_back(token::TokenDescriptor(name, kind, group));
  token::TokenDescriptor *ptr = &storage_.back();

  by_kind_[kind] = ptr;
  by_name_[name] = ptr;
  trie_.insert(name, ptr);

  return *ptr;
}

token::TokenDescriptor &DescriptorTable::add(token::TokenKind kind,
                                             token::TokenGroup group) {
  storage_.emplace_back(U"", kind, group);
  token::TokenDescriptor *ptr = &storage_.back();

  by_kind_[kind] = ptr;

  return *ptr;
}
token::TokenDescriptor *DescriptorTable::lookup_by_kind(token::TokenKind kind) {
  auto it = by_kind_.find(kind);
  return it != by_kind_.end() ? it->second : nullptr;
}

token::TokenDescriptor *
DescriptorTable::lookup_by_name(const std::u32string_view &name) {
  auto it = by_name_.find(name);
  return it != by_name_.end() ? it->second : nullptr;
}

} // namespace core::table