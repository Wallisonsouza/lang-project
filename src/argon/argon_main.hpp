#pragma once

#include "core/LangData.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"

namespace argon {

inline void bind(interpreter::core::LangData &data) {

  using namespace interpreter::core;

  data.precedence_table.add(interpreter::core::TokenKind::Assign, 1, true);
  data.precedence_table.add(interpreter::core::TokenKind::Plus, 10);
  data.precedence_table.add(interpreter::core::TokenKind::Minus, 10);
  data.precedence_table.add(interpreter::core::TokenKind::Star, 20);
  data.precedence_table.add(interpreter::core::TokenKind::Slash, 20);

  data.token_table.add(interpreter::core::TokenKind::Plus, U"+", interpreter::core::TokenGroup::Operator);
  data.token_table.add(interpreter::core::TokenKind::Minus, U"-", interpreter::core::TokenGroup::Operator);
  data.token_table.add(interpreter::core::TokenKind::Star, U"*", interpreter::core::TokenGroup::Operator);
  data.token_table.add(interpreter::core::TokenKind::Slash, U"/", interpreter::core::TokenGroup::Operator);

  data.token_table.add(interpreter::core::TokenKind::Assign, U"=", interpreter::core::TokenGroup::Operator);

  data.alias_table.add(U"->", data.token_table.lookup_by_kind(interpreter::core::TokenKind::Assign));
  data.alias_table.add(U"<-", data.token_table.lookup_by_kind(interpreter::core::TokenKind::Assign));
  data.token_table.add(interpreter::core::TokenKind::Equals, U"==", interpreter::core::TokenGroup::Operator);
  data.token_table.add(interpreter::core::TokenKind::Ternary, U"?", interpreter::core::TokenGroup::Operator);

  data.token_table.add(interpreter::core::TokenKind::LParen, U"(", interpreter::core::TokenGroup::Punctuation);
  data.token_table.add(interpreter::core::TokenKind::Colon, U":", interpreter::core::TokenGroup::Punctuation);
  data.token_table.add(interpreter::core::TokenKind::RParen, U")", interpreter::core::TokenGroup::Punctuation);
  data.token_table.add(interpreter::core::TokenKind::LBrace, U"{", interpreter::core::TokenGroup::Punctuation);
  data.token_table.add(interpreter::core::TokenKind::RBrace, U"}", interpreter::core::TokenGroup::Punctuation);
  data.token_table.add(interpreter::core::TokenKind::Semicolon, U";", interpreter::core::TokenGroup::Punctuation);
  data.token_table.add(interpreter::core::TokenKind::Comma, U",", interpreter::core::TokenGroup::Punctuation);
  data.token_table.add(interpreter::core::TokenKind::SingleQuote, U"\'", interpreter::core::TokenGroup::Punctuation);

  data.token_table.add(TokenKind::Identifier, TokenGroup::Name);

  data.token_table.add(TokenKind::NumberLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::NumberType, U"Number", TokenGroup::Type);
  data.token_table.add(TokenKind::StringLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::BoolLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::CharLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::NullLiteral, TokenGroup::Literal);
}
} // namespace argon
