#include "core/node/flags.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_variable_declaration() {
  auto mods = parse_modifiers();

  if (!unit.tokens.match(TokenKind::VALUE_KEYWORD) &&
      !unit.tokens.match(TokenKind::CONST_KEYWORD)) {
    return nullptr;
  }

  auto *pattern = parse_pattern(mods);

  if (pattern->flags.has(NodeFlags::HasError)) {
    recover_until(RecoverBoundary::Variable);
  }

  return pattern;
}
