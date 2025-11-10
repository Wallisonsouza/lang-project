#pragma once

#include "core/token/TokenDescriptor.hpp"
#include <deque>
#include <unordered_map>

class TokenTable {
public:
  TokenDescriptor &register_token(TokenKind kind, const std::u32string &name, TokenGroup group) {
    TokenDescriptor descriptor{kind, group, name, {}};
    descriptors_.push_back(descriptor);
    TokenDescriptor *ptr = &descriptors_.back();

    lookup_by_kind_[kind] = ptr;
    lookup_by_name_[name] = ptr;
    return *ptr;
  }

  void register_alias(TokenKind kind, const std::u32string &alias) {
    TokenDescriptor *desc = get_descriptor(kind);
    if (!desc)
      return;
    desc->add_alias(alias);
    lookup_by_name_[alias] = desc;
  }

  TokenDescriptor *get_descriptor(TokenKind kind) {
    if (auto it = lookup_by_kind_.find(kind); it != lookup_by_kind_.end())
      return it->second;
    return nullptr;
  }

  TokenDescriptor *get_descriptor(const std::u32string &name) {
    if (auto it = lookup_by_name_.find(name); it != lookup_by_name_.end())
      return it->second;
    return nullptr;
  }

private:
  std::deque<TokenDescriptor> descriptors_;
  std::unordered_map<TokenKind, TokenDescriptor *> lookup_by_kind_;
  std::unordered_map<std::u32string, TokenDescriptor *> lookup_by_name_;
};