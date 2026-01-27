#pragma once

#include "core/token/TokenKind.hpp"
#include <unordered_map>

namespace core::table {

class PrecedenceTable {
public:
  void add(TokenKind kind, int precedence, bool right_assoc = false);

  bool has(TokenKind kind) const;

  int get_precedence(TokenKind kind) const;
  bool is_right_associative(TokenKind kind) const;

private:
  struct OperatorInfo {
    int precedence;
    bool right_assoc;
  };

  std::unordered_map<TokenKind, OperatorInfo> table;
};

} // namespace core::table
