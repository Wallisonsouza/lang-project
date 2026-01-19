#include "core/node/Modifier.hpp"
#include "engine/parser/parser.hpp"

core::node::Modifiers Parser::parse_modifiers() {
  core::node::Modifiers mods;

  while (auto *tok = unit.tokens.peek()) {
    switch (tok->descriptor->kind) {
    case core::token::TokenKind::STATIC:
      mods.add(core::node::Modifier::Static);
      break;
    case core::token::TokenKind::MUT:
      mods.add(core::node::Modifier::Mut);
      break;
    case core::token::TokenKind::PUBLIC:
      mods.add(core::node::Modifier::Public);
      break;
    case core::token::TokenKind::PRIVATE:
      mods.add(core::node::Modifier::Private);
      break;
    default:
      return mods;
    }
    unit.tokens.advance();
  }

  return mods;
}