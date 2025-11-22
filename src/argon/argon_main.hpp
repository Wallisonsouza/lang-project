#pragma once

#include "argon/matchers/IdentifierMatcher.hpp"
#include "argon/matchers/NumberMatcher.hpp"
#include "argon/matchers/Operator.hpp"
#include "argon/matchers/String.hpp"
#include "core/LangData.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"

namespace argon {

inline void bind(lang::core::LangData &data) {

  data.token_table.add_token(lang::core::TokenKind::Function, U"func", lang::core::TokenGroup::Keyword);
  data.token_table.add_token(lang::core::TokenKind::Variable, U"let", lang::core::TokenGroup::Keyword);
  data.token_table.add_token(lang::core::TokenKind::If, U"if", lang::core::TokenGroup::Keyword);
  data.token_table.add_token(lang::core::TokenKind::Else, U"else", lang::core::TokenGroup::Keyword);
  data.token_table.add_token(lang::core::TokenKind::While, U"while", lang::core::TokenGroup::Keyword);
  data.token_table.add_token(lang::core::TokenKind::For, U"for", lang::core::TokenGroup::Keyword);
  data.token_table.add_token(lang::core::TokenKind::Return, U"return", lang::core::TokenGroup::Keyword);

  data.token_table.add_token(lang::core::TokenKind::Plus, U"+", lang::core::TokenGroup::Operator);
  data.token_table.add_token(lang::core::TokenKind::Minus, U"-", lang::core::TokenGroup::Operator);
  data.token_table.add_token(lang::core::TokenKind::Star, U"*", lang::core::TokenGroup::Operator);
  data.token_table.add_token(lang::core::TokenKind::Slash, U"/", lang::core::TokenGroup::Operator);
  data.token_table.add_token(lang::core::TokenKind::Assign, U"=", lang::core::TokenGroup::Operator);
  data.token_table.add_token(lang::core::TokenKind::Equals, U"==", lang::core::TokenGroup::Operator);
  data.token_table.add_token(lang::core::TokenKind::Ternary, U"?", lang::core::TokenGroup::Operator);

  data.token_table.add_token(lang::core::TokenKind::LParen, U"(", lang::core::TokenGroup::Punctuation);
  data.token_table.add_token(lang::core::TokenKind::Colon, U":", lang::core::TokenGroup::Punctuation);

  data.token_table.add_token(lang::core::TokenKind::RParen, U")", lang::core::TokenGroup::Punctuation);
  data.token_table.add_token(lang::core::TokenKind::LBrace, U"{", lang::core::TokenGroup::Punctuation);
  data.token_table.add_token(lang::core::TokenKind::RBrace, U"}", lang::core::TokenGroup::Punctuation);
  data.token_table.add_token(lang::core::TokenKind::Semicolon, U";", lang::core::TokenGroup::Punctuation);
  data.token_table.add_token(lang::core::TokenKind::Comma, U",", lang::core::TokenGroup::Punctuation);
  data.token_table.add_token(lang::core::TokenKind::SingleQuote, U"\'", lang::core::TokenGroup::Punctuation);

  data.token_table.add_token(lang::core::TokenKind::Identifier, U"identifier", lang::core::TokenGroup::Literal);
  data.token_table.add_token(lang::core::TokenKind::Number, U"number", lang::core::TokenGroup::Literal);
  data.token_table.add_token(lang::core::TokenKind::String, U"string", lang::core::TokenGroup::Literal);
  data.token_table.add_token(lang::core::TokenKind::EndOfFile, U"eof", lang::core::TokenGroup::Error);

  data.matchers.add(std::make_unique<argon::matchers::StringMatcher>());
  data.matchers.add(std::make_unique<argon::matchers::IdentifierMatcher>());
  data.matchers.add(std::make_unique<argon::matchers::OperatorMatcher>());
  data.matchers.add(std::make_unique<argon::matchers::NumberMatcher>());

  // data.matchers.push_back({argon::matchers::match_operator, 0});
}
} // namespace argon
