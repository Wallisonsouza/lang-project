#pragma once
#include "core/token/Token.hpp"
#include "parser/node/statement_nodes.hpp"
#include "utils/Stream.hpp"

namespace parser::match {
inline node::Modifier match_modifier(utils::Stream<core::token::Token *> &stream) {

  node::Modifier mods = node::Modifier::None;

  while (!stream.is_end()) {

    auto token = stream.peek();

    if (!token) break;

    switch (token->descriptor->kind) {
    case core::token::TokenKind::Value: mods = mods | node::Modifier::Value; break;
    case core::token::TokenKind::Static: mods = mods | node::Modifier::Static; break;
    case core::token::TokenKind::Mut: mods = mods | node::Modifier::Mut; break;
    case core::token::TokenKind::Public: mods = mods | node::Modifier::Public; break;
    case core::token::TokenKind::Private: mods = mods | node::Modifier::Private; break;
    default: return mods;
    }

    stream.advance();
  }

  return mods;
}

} // namespace parser::match