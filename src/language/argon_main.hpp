#pragma once
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "engine/language_context.hpp"
#include "language/module_console.hpp"

namespace ayla::language {

inline LanguageContext create_context() {

  using namespace core::token;

  auto context = LanguageContext();

  auto parent = context.modules.create_module("debug");
  ayla::modules::create_module_console(context, parent);
  ayla::modules::create_module_math(context);

  context.precedence_table.add(TokenKind::Assign, 1, true);
  context.precedence_table.add(TokenKind::Equals, 5, false);

  context.descriptor_table.add(TokenKind::LessThan, "<", TokenGroup::Operator);
  context.precedence_table.add(TokenKind::LessThan, 6, false);

  context.precedence_table.add(TokenKind::Plus, 10, false);
  context.precedence_table.add(TokenKind::Minus, 10, false);
  context.precedence_table.add(TokenKind::Star, 20, false);
  context.precedence_table.add(TokenKind::Slash, 20, false);

  // context.precedence_table.add(TokenKind::NotEqual, 5, false);     // !=

  // context.precedence_table.add(TokenKind::LessEqual, 6, false);    // <=
  // context.precedence_table.add(TokenKind::Greater, 6, false);      // >
  // context.precedence_table.add(TokenKind::GreaterEqual, 6, false); // >=

  context.descriptor_table.add(TokenKind::AsKeyword, "as", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::IfKeyword, "if", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::ElseKeyword, "else", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::FunctionKeyword, "fn", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::ReturnKeyword, "return", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::ImportKeyword, "import", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::Static, "static", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::Mut, "mut", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::ValueKeyword, "val", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::Public, "public", TokenGroup::Keyword);
  context.descriptor_table.add(TokenKind::Private, "private", TokenGroup::Keyword);

  context.descriptor_table.add(TokenKind::Plus, "+", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Minus, "-", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Star, "*", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Slash, "/", TokenGroup::Operator);

  context.descriptor_table.add(TokenKind::Assign, "=", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Arrow, "->", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Equals, "==", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::Ternary, "?", TokenGroup::Operator);
  context.descriptor_table.add(TokenKind::GreaterThan, ">", TokenGroup::Operator);

  context.descriptor_table.add(TokenKind::OpenParen, "(", TokenGroup::Punctuation);

  context.descriptor_table.add(TokenKind::Colon, ":", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::Dot, ".", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CloseParen, ")", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::OpenBrace, "{", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CloseBrace, "}", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::OpenBracket, "[", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::CloseBracket, "]", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::Semicolon, ";", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::Comma, ",", TokenGroup::Punctuation);
  context.descriptor_table.add(TokenKind::SingleQuote, "\'", TokenGroup::Punctuation);

  context.descriptor_table.add(TokenKind::Identifier, TokenGroup::Name);

  context.descriptor_table.add(TokenKind::NumberLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::StringLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::BoolLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::CharLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::NullLiteral, TokenGroup::Literal);
  context.descriptor_table.add(TokenKind::Newline, "\\n", TokenGroup::Whitespace);

  return context;
}
} // namespace ayla::language
