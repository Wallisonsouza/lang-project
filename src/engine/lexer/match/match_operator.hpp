#pragma once

#include "core/source/TextStream.hpp"
#include "core/token/Token.hpp"
#include "engine/CompilationUnit.hpp"

namespace lexer::match {

inline core::token::Token *match_operator(CompilationUnit &unit,
                                          core::source::TextStream &stream) {
  auto start = stream.get_state();

  const auto *node = unit.context.alias_table.trie().root();
  const core::token::TokenDescriptor *best = nullptr;
  size_t best_len = 0;
  assert(unit.context.alias_table.trie().root()->child(U':') != nullptr);

  size_t offset = 0;

  while (true) {
    char32_t c = stream.peek(offset);
    if (!c)
      break;

    node = node->child(c);
    if (!node)
      break;

    offset++;

    if (node->is_terminal) {
      best = node->value;
      best_len = offset;
    }
  }

  if (!best)
    return nullptr;

  stream.advance_n(best_len);

  auto slice = stream.slice_from(start);

  return unit.tokens.create_token<core::token::Token>(best, slice);
}

} // namespace lexer::match
