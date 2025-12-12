#pragma once

#include "core/LangData.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"

namespace argon {

inline void bind(core::LangData &data) {

  using namespace core::token;

  data.precedence_table.add(TokenKind::Assign, 1, true);
  data.precedence_table.add(TokenKind::Plus, 10);
  data.precedence_table.add(TokenKind::Minus, 10);
  data.precedence_table.add(TokenKind::Star, 20);
  data.precedence_table.add(TokenKind::Slash, 20);

  data.token_table.add(TokenKind::Plus, U"+", TokenGroup::Operator);
  data.token_table.add(TokenKind::Minus, U"-", TokenGroup::Operator);
  data.token_table.add(TokenKind::Star, U"*", TokenGroup::Operator);
  data.token_table.add(TokenKind::Slash, U"/", TokenGroup::Operator);

  data.token_table.add(TokenKind::Assign, U"=", TokenGroup::Operator);

  data.alias_table.add(U"->",
                       data.token_table.lookup_by_kind(TokenKind::Assign));
  data.alias_table.add(U"<-",
                       data.token_table.lookup_by_kind(TokenKind::Assign));
  data.token_table.add(TokenKind::Equals, U"==", TokenGroup::Operator);
  data.token_table.add(TokenKind::Ternary, U"?", TokenGroup::Operator);

  data.token_table.add(TokenKind::LParen, U"(", TokenGroup::Punctuation);
  data.token_table.add(TokenKind::Colon, U":", TokenGroup::Punctuation);
  data.token_table.add(TokenKind::RParen, U")", TokenGroup::Punctuation);
  data.token_table.add(TokenKind::LBrace, U"{", TokenGroup::Punctuation);
  data.token_table.add(TokenKind::RBrace, U"}", TokenGroup::Punctuation);
  data.token_table.add(TokenKind::Semicolon, U";", TokenGroup::Punctuation);
  data.token_table.add(TokenKind::Comma, U",", TokenGroup::Punctuation);
  data.token_table.add(TokenKind::SingleQuote, U"\'", TokenGroup::Punctuation);

  data.token_table.add(TokenKind::Identifier, TokenGroup::Name);

  data.token_table.add(TokenKind::NumberLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::NumberType, U"Number", TokenGroup::Type);
  data.token_table.add(TokenKind::StringType, U"String", TokenGroup::Type);
  data.token_table.add(TokenKind::StringLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::BoolLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::CharLiteral, TokenGroup::Literal);
  data.token_table.add(TokenKind::NullLiteral, TokenGroup::Literal);
}
} // namespace argon
