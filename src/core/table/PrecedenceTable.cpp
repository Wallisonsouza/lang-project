#include "core/table/PrecedenceTable.hpp"

namespace interpreter::core {

void PrecedenceTable::add(core::TokenKind kind, int precedence, bool right_assoc) { table[kind] = OperatorInfo{precedence, right_assoc}; }

bool PrecedenceTable::has(core::TokenKind kind) const { return table.find(kind) != table.end(); }

int PrecedenceTable::get_precedence(core::TokenKind kind) const {
  auto it = table.find(kind);
  if (it == table.end()) return -1;
  return it->second.precedence;
}

bool PrecedenceTable::is_right_associative(core::TokenKind kind) const {
  auto it = table.find(kind);
  if (it == table.end()) return false;
  return it->second.right_assoc;
}

} // namespace interpreter::core
