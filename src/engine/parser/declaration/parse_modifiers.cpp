#include "core/node/Modifier.hpp"
#include "engine/parser/parser.hpp"

core::node::Modifiers Parser::parse_modifiers() {
  core::node::Modifiers mods;

  while (auto *tok = unit.tokens.peek()) {
    switch (tok->descriptor->kind) {
    case core::token::TokenKind::ValueKeyword: mods.add(core::node::Modifier::Value); break;
    case core::token::TokenKind::Static: mods.add(core::node::Modifier::Static); break;
    case core::token::TokenKind::Mut: mods.add(core::node::Modifier::Mut); break;
    case core::token::TokenKind::Public: mods.add(core::node::Modifier::Public); break;
    case core::token::TokenKind::Private: mods.add(core::node::Modifier::Private); break;
    default: return mods;
    }
    unit.tokens.advance();
  }

  return mods;
}