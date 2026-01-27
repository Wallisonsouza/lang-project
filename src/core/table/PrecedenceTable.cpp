#include "core/table/PrecedenceTable.hpp"
#include "core/token/TokenKind.hpp"

namespace core::table {

void PrecedenceTable::add(TokenKind kind, int precedence, bool right_assoc) {
  table[kind] = OperatorInfo{precedence, right_assoc};
}

bool PrecedenceTable::has(TokenKind kind) const {
  return table.find(kind) != table.end();
}

int PrecedenceTable::get_precedence(TokenKind kind) const {
  auto it = table.find(kind);
  if (it == table.end())
    return -1;
  return it->second.precedence;
}

bool PrecedenceTable::is_right_associative(TokenKind kind) const {
  auto it = table.find(kind);
  if (it == table.end())
    return false;
  return it->second.right_assoc;
}

} // namespace core::table
