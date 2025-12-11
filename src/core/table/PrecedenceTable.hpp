#pragma once

#include "core/token/TokenKind.hpp"
#include <unordered_map>

namespace interpreter::core {

class PrecedenceTable {
public:
  void add(core::TokenKind kind, int precedence, bool right_assoc = false);

  bool has(core::TokenKind kind) const;

  int get_precedence(core::TokenKind kind) const;
  bool is_right_associative(core::TokenKind kind) const;

private:
  struct OperatorInfo {
    int precedence;
    bool right_assoc;
  };

  std::unordered_map<core::TokenKind, OperatorInfo> table;
};

} // namespace interpreter::core
