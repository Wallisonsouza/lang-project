#pragma once

#include "core/token/TokenKind.hpp"
#include <unordered_map>

namespace lang::debug {

class TokenKindTable {
public:
  static const std::unordered_map<lang::core::TokenKind, const char *> kind_map;

  static const char *get_token_kind_name(lang::core::TokenKind kind) {
    auto it = kind_map.find(kind);
    if (it != kind_map.end()) {
      return it->second;
    }
    return "[Unknown Kind]";
  }
};

} // namespace lang::debug
