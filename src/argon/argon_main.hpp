#pragma once
#include "argon/handlers/KeywordAndIdentifierHandler.hpp"
#include "argon/handlers/SymbolHandler.hpp"
#include "core/LangData.hpp"
#include "core/plugin/Plugin.hpp"

using namespace lang::core;
using namespace lang::utils;

#pragma once
#include "core/LangData.hpp"
#include "core/token/TokenTable.hpp"
#include <string>

namespace argon {

inline void create_tokens_context(lang::core::LangData &data) {
  // =====================
  // 🔹 Keywords
  // =====================
  data.descriptors.register_token(TokenKind::If, U"if", TokenGroup::Keyword);
  data.descriptors.register_token(TokenKind::Else, U"else", TokenGroup::Keyword);
  data.descriptors.register_token(TokenKind::While, U"while", TokenGroup::Keyword);
  data.descriptors.register_token(TokenKind::For, U"for", TokenGroup::Keyword);
  data.descriptors.register_token(TokenKind::Return, U"return", TokenGroup::Keyword);

  // =====================
  // 🔹 Operators
  // =====================
  data.descriptors.register_token(TokenKind::Plus, U"+", TokenGroup::Operator);

  data.descriptors.register_token(TokenKind::Minus, U"-", TokenGroup::Operator);
  data.descriptors.register_token(TokenKind::Star, U"*", TokenGroup::Operator);
  data.descriptors.register_token(TokenKind::Slash, U"/", TokenGroup::Operator);
  data.descriptors.register_token(TokenKind::Assign, U"=", TokenGroup::Operator);

  // =====================
  // 🔹 Punctuation
  // =====================
  data.descriptors.register_token(TokenKind::LParen, U"(", TokenGroup::Punctuation);
  data.descriptors.register_token(TokenKind::RParen, U")", TokenGroup::Punctuation);
  data.descriptors.register_token(TokenKind::LBrace, U"{", TokenGroup::Punctuation);
  data.descriptors.register_token(TokenKind::RBrace, U"}", TokenGroup::Punctuation);
  data.descriptors.register_token(TokenKind::Semicolon, U";", TokenGroup::Punctuation);

  // =====================
  // 🔹 Others
  // =====================
  data.descriptors.register_token(TokenKind::Identifier, U"identifier", TokenGroup::Identifier);
  data.descriptors.register_token(TokenKind::Number, U"number", TokenGroup::Literal);
  data.descriptors.register_token(TokenKind::String, U"string", TokenGroup::Literal);
  data.descriptors.register_token(TokenKind::EndOfFile, U"eof", TokenGroup::Error);
}

inline void create_tokens_handler(lang::core::LangData &data) {

  auto keyword_ptr = std::make_shared<plugins::UniqueCharHandler>();

  data.handlers.add(keyword_ptr, 0);
}

} // namespace argon
