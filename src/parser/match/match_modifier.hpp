#pragma once
#include "core/TokenStream.hpp"
#include "core/token/Token.hpp"
#include "parser/node/statement_nodes.hpp"

namespace parser::match {
inline core::node::Modifier match_modifier(TokenStream &stream) {

  core::node::Modifier mods = core::node::Modifier::None;

  while (!stream.is_end()) {

    auto token = stream.peek();

    if (!token)
      break;

    switch (token->descriptor->kind) {
    case core::token::TokenKind::Value:
      mods = mods | core::node::Modifier::Value;
      break;
    case core::token::TokenKind::Static:
      mods = mods | core::node::Modifier::Static;
      break;
    case core::token::TokenKind::Mut:
      mods = mods | core::node::Modifier::Mut;
      break;
    case core::token::TokenKind::Public:
      mods = mods | core::node::Modifier::Public;
      break;
    case core::token::TokenKind::Private:
      mods = mods | core::node::Modifier::Private;
      break;
    default:
      return mods;
    }

    stream.advance();
  }

  return mods;
}

} // namespace parser::match