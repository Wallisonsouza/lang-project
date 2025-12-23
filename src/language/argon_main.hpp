#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "language/LanguageSpec.hpp"

namespace ayla::language {

inline LanguageSpec make_lang_context() {

  using namespace core::token;

  auto context = LanguageSpec();

  context.precedence_table.add(TokenKind::Assign, 1, true);

  context.precedence_table.add(TokenKind::Plus, 10);
  context.precedence_table.add(TokenKind::Minus, 10);

  context.precedence_table.add(TokenKind::Star, 20);
  context.precedence_table.add(TokenKind::Slash, 20);

  context.descriptor_table.add(TokenKind::FunctionKeyword, U"fn",
                               TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::UseKeyword, U"use",
                               TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::Static, U"static",
                               TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::Mut, U"mut", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::Value, U"val", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::Public, U"public",
                               TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::Private, U"private",
                               TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::Plus, U"+", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Minus, U"-", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Star, U"*", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Slash, U"/", TokenGroup::Operator);

  context.descriptor_table.add(TokenKind::Assign, U"=", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Arrow, U"->", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Equals, U"==", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Ternary, U"?", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::GreaterThan, U">",
                               TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::LessThan, U"<", TokenGroup::Operator);

  context.descriptor_table.add(TokenKind::OpenParen, U"(",
                               TokenGroup::Punctuation);

  context.descriptor_table.add(TokenKind::Colon, U":", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::Dot, U".", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CloseParen, U")",
                               TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::OpenBrace, U"{",
                               TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CloseBrace, U"}",
                               TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::Semicolon, U";",
                               TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::Comma, U",", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::SingleQuote, U"\'",
                               TokenGroup::Punctuation);

  context.descriptor_table.add(TokenKind::Identifier, TokenGroup::Name);

  context.descriptor_table.add(TokenKind::NumberLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::StringLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::BoolLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::CharLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::NullLiteral, TokenGroup::Literal);

  return context;
}
} // namespace ayla::language
