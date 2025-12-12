#include "AliasTable.hpp"
#include "core/token/TokenKind.hpp"
#include <string>
#include <string_view>

namespace core::table {

void AliasTable::add(const std::u32string &alias,
                     token::TokenDescriptor *descriptor) {

  if (has_alias(alias) || !descriptor)
    return;

  by_name_[alias] = descriptor;

  by_kind_[descriptor->kind].push_back(alias);

  trie_.insert(alias, descriptor);
}

bool AliasTable::has_prefix(const std::u32string_view &prefix) const {
  return trie_.has_prefix(prefix);
}

token::TokenDescriptor *
AliasTable::lookup_by_name(const std::u32string_view &alias) const {
  auto it = by_name_.find(alias);
  return it == by_name_.end() ? nullptr : it->second;
}

bool AliasTable::has_alias(const std::u32string_view &alias) const {
  return by_name_.contains(alias);
}

const std::vector<std::u32string_view> &
AliasTable::get_aliases(token::TokenKind kind) const {
  static const std::vector<std::u32string_view> empty;

  auto it = by_kind_.find(kind);
  return it == by_kind_.end() ? empty : it->second;
}

void AliasTable::clear() {
  by_name_.clear();
  by_kind_.clear();
  trie_.clear();
}

} // namespace core::table
