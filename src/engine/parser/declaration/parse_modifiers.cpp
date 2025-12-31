#include "parse_modifiers.hpp"

namespace parser::declaration {

core::node::Modifiers parse_modifiers(core::token::TokenStream &stream) {
  core::node::Modifiers mods;

  while (auto *tok = stream.peek()) {
    switch (tok->descriptor->kind) {
    case core::token::TokenKind::Value: mods.add(core::node::Modifier::Value); break;
    case core::token::TokenKind::Static: mods.add(core::node::Modifier::Static); break;
    case core::token::TokenKind::Mut: mods.add(core::node::Modifier::Mut); break;
    case core::token::TokenKind::Public: mods.add(core::node::Modifier::Public); break;
    case core::token::TokenKind::Private: mods.add(core::node::Modifier::Private); break;
    default: return mods;
    }
    stream.advance();
  }

  return mods;
}

} // namespace parser::declaration
