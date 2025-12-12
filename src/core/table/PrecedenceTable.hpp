#pragma once

#include "core/token/TokenKind.hpp"
#include <unordered_map>

namespace core::table {

class PrecedenceTable {
public:
  void add(token::TokenKind kind, int precedence, bool right_assoc = false);

  bool has(token::TokenKind kind) const;

  int get_precedence(token::TokenKind kind) const;
  bool is_right_associative(token::TokenKind kind) const;

private:
  struct OperatorInfo {
    int precedence;
    bool right_assoc;
  };

  std::unordered_map<token::TokenKind, OperatorInfo> table;
};

} // namespace core::table
