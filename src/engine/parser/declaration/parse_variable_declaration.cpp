#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_variable_declaration() {
  auto mods = parse_modifiers();

  if (!unit.tokens.match(core::token::TokenKind::ValueKeyword) && !unit.tokens.match(core::token::TokenKind::ConstKeyword)) return nullptr;

  auto *pattern = parse_pattern(mods);
  if (!pattern) return nullptr;

  return pattern;
}
