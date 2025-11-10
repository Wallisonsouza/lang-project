#pragma once
#include "core/token/Token.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "core/utils/Utf8.hpp"
#include <iostream>
#include <memory>

template <typename T> struct TokenDebug {
  T type;
  const char *name;
};

inline constexpr TokenDebug<TokenKind> token_kind_debug_table[] = {
    {TokenKind::If, "If"},         {TokenKind::Else, "Else"},     {TokenKind::While, "While"},         {TokenKind::For, "For"},
    {TokenKind::Return, "Return"}, {TokenKind::Plus, "Plus"},     {TokenKind::Minus, "Minus"},         {TokenKind::Star, "Star"},
    {TokenKind::Slash, "Slash"},   {TokenKind::Assign, "Assign"}, {TokenKind::LParen, "LParen"},       {TokenKind::RParen, "RParen"},
    {TokenKind::LBrace, "LBrace"}, {TokenKind::RBrace, "RBrace"}, {TokenKind::Semicolon, "Semicolon"}, {TokenKind::Identifier, "Identifier"},
    {TokenKind::Number, "Number"}, {TokenKind::String, "String"}, {TokenKind::EndOfFile, "EndOfFile"},
};

inline constexpr TokenDebug<TokenGroup> token_group_debug_table[] = {
    {TokenGroup::Keyword, "Keyword"}, {TokenGroup::Operator, "Operator"}, {TokenGroup::Punctuation, "Punctuation"}, {TokenGroup::Literal, "Literal"}, {TokenGroup::Identifier, "Identifier"},
    {TokenGroup::Type, "Type"},       {TokenGroup::Error, "Error"},
};

namespace lang::debug {

inline void debug_token(const std::shared_ptr<core::Token> &token) {
  if (!token || !token->descriptor)
    return;

  const auto group_idx = static_cast<size_t>(token->descriptor->group);
  const auto kind_idx  = static_cast<size_t>(token->descriptor->kind);

  if (group_idx >= sizeof(token_group_debug_table) / sizeof(token_group_debug_table[0]) || kind_idx >= sizeof(token_kind_debug_table) / sizeof(token_kind_debug_table[0])) {
    std::cout << "[Invalid token]";
    return;
  }

  std::cout << "Token: " << lang::utils::Utf8Codec::encode(token->lexeme)  << " | " << "Kind: " << token_kind_debug_table[kind_idx].name << " | Group: " << token_group_debug_table[group_idx].name << "\n";
}

} // namespace lang::debug
