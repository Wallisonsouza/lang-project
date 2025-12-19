#include "AliasTable.hpp"
#include "core/token/TokenDescriptor.hpp"
#include "core/token/TokenKind.hpp"
#include "utils/Utf8.hpp"
#include <iostream>
#include <string>
#include <string_view>

namespace core::table {

void AliasTable::add(const std::u32string &alias, token::TokenKind kind) {
  auto desc = descriptor_table.lookup_by_kind(kind);
  if (!desc || has_alias(alias)) return;

  by_name_[alias] = desc;
  by_kind_[desc->kind].push_back(alias);
  trie_.insert(alias, desc);
}

bool AliasTable::has_prefix(const std::u32string_view &prefix) const { return trie_.has_prefix(prefix); }

token::TokenDescriptor *AliasTable::lookup_by_name(const std::u32string_view &alias) const {
  auto it = by_name_.find(alias);
  return it == by_name_.end() ? nullptr : it->second;
}

bool AliasTable::has_alias(const std::u32string_view &alias) const { return by_name_.contains(alias); }

token::TokenDescriptor *AliasTable::resolve_alias(const std::u32string_view &alias) const {
  auto it = by_name_.find(alias);
  if (it != by_name_.end()) { return it->second; }

  return descriptor_table.lookup_by_name(alias);
}

const std::vector<std::u32string> &AliasTable::get_aliases(token::TokenKind kind) const {
  auto it = by_kind_.find(kind);
  static const std::vector<std::u32string> empty;
  return it != by_kind_.end() ? it->second : empty;
}

void AliasTable::clear() {
  by_name_.clear();
  by_kind_.clear();
  trie_.clear();
}
void AliasTable::build() {
  clear();

  for (auto &[alias, desc_ptr] : descriptor_table.all_names()) {
    by_name_[alias] = desc_ptr;
    by_kind_[desc_ptr->kind].push_back(alias); // sempre desc_ptr->kind
    trie_.insert(alias, desc_ptr);
  }
}

} // namespace core::table
