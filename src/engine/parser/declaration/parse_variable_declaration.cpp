#include "core/node/flags.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_variable_declaration() {
  auto mods = parse_modifiers();

  if (!unit.tokens.match(core::token::TokenKind::VALUE_KEYWORD) &&
      !unit.tokens.match(core::token::TokenKind::CONST_KEYWORD)) {
    return nullptr;
  }

  auto *pattern = parse_pattern(mods);

  if (pattern && has_flag(pattern->flags, NodeFlags::HasError)) {
    synchronize_statement();
  }

  return pattern;
}
