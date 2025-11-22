#include "AliasTable.hpp"

void AliasTable::add_alias(const std::u32string &alias, TokenDescriptor *descriptor) {
  if (has_alias(alias))
    return;

  by_name_[alias] = descriptor;
  trie_.insert(alias, descriptor);
}

bool AliasTable::has_prefix(const std::u32string &prefix) const { return trie_.has_prefix(prefix); }

TokenDescriptor *AliasTable::lookup_by_name(const std::u32string &alias) const {
  auto it = by_name_.find(alias);
  return it == by_name_.end() ? nullptr : it->second;
}

bool AliasTable::has_alias(const std::u32string &alias) const { return by_name_.count(alias) != 0; }

void AliasTable::clear() {
  by_name_.clear();
  trie_.clear();
}
