#include "core/node/Modifier.hpp"
#include "engine/parser/parser.hpp"

core::ast::Modifiers Parser::parse_modifiers() {
  core::ast::Modifiers mods;

  while (auto *tok = unit.tokens.peek()) {
    switch (tok->descriptor->kind) {
    case TokenKind::STATIC: mods.add(core::ast::Modifier::Static); break;
    case TokenKind::MUT: mods.add(core::ast::Modifier::Mut); break;
    case TokenKind::PUBLIC: mods.add(core::ast::Modifier::Public); break;
    case TokenKind::PRIVATE: mods.add(core::ast::Modifier::Private); break;
    default: return mods;
    }
    unit.tokens.advance();
  }

  return mods;
}