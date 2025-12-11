#pragma once
#include "core/LangData.hpp"
#include "core/debug/Console.hpp"
#include "core/token/Token.hpp"
#include "core/utils/Utf8.hpp"
#include <string>
#include <unordered_map>

namespace interpreter::debug {
class TokenDebug {

private:
  inline static const std::unordered_map<interpreter::core::TokenGroup, const std::string> group_map = {
      {interpreter::core::TokenGroup::Name, "Name"},         {interpreter::core::TokenGroup::Keyword, "Keyword"},
      {interpreter::core::TokenGroup::Operator, "Operator"}, {interpreter::core::TokenGroup::Punctuation, "Punctuation"},
      {interpreter::core::TokenGroup::Literal, "Literal"},   {interpreter::core::TokenGroup::Type, "Type"},
      {interpreter::core::TokenGroup::Error, "Error"},
  };

  inline static const std::unordered_map<interpreter::core::TokenKind, const std::string> kind_map = {
      {interpreter::core::TokenKind::NumberType, "NumberType"},
      {interpreter::core::TokenKind::Function, "Function"},
      {interpreter::core::TokenKind::If, "If"},
      {interpreter::core::TokenKind::Equals, "Equals"},
      {interpreter::core::TokenKind::Ternary, "Ternary"},
      {interpreter::core::TokenKind::Space, "Space"},
      {interpreter::core::TokenKind::Variable, "Variable"},
      {interpreter::core::TokenKind::Colon, "Colon"},
      {interpreter::core::TokenKind::DoubleQuote, "DoubleQuote"},
      {interpreter::core::TokenKind::SingleQuote, "SingleQuote"},
      {interpreter::core::TokenKind::Comma, "Comma"},
      {interpreter::core::TokenKind::Else, "Else"},
      {interpreter::core::TokenKind::While, "While"},
      {interpreter::core::TokenKind::For, "For"},
      {interpreter::core::TokenKind::Return, "Return"},
      {interpreter::core::TokenKind::Plus, "Plus"},
      {interpreter::core::TokenKind::Minus, "Minus"},
      {interpreter::core::TokenKind::Star, "Star"},
      {interpreter::core::TokenKind::Slash, "Slash"},
      {interpreter::core::TokenKind::Assign, "Assign"},
      {interpreter::core::TokenKind::LParen, "LParen"},
      {interpreter::core::TokenKind::RParen, "RParen"},
      {interpreter::core::TokenKind::LBrace, "LBrace"},
      {interpreter::core::TokenKind::RBrace, "RBrace"},
      {interpreter::core::TokenKind::Semicolon, "Semicolon"},
      {interpreter::core::TokenKind::Identifier, "Identifier"},
      {interpreter::core::TokenKind::NumberLiteral, "NumberLiteral"},
      {interpreter::core::TokenKind::StringLiteral, "StringLiteral"},
      {interpreter::core::TokenKind::EndOfFile, "EndOfFile"},
  };

  static const std::string get_kind(interpreter::core::TokenKind kin) {
    auto it = kind_map.find(kin);
    if (it != kind_map.end()) return std::string(it->second);
    return "[UnknownKind]";
  }

  static const std::string get_group(interpreter::core::TokenGroup grp) {
    auto it = group_map.find(grp);
    if (it != group_map.end()) return std::string(it->second);
    return "[UnknownGroup]";
  }

public:
#define C_RESET "\033[0m"
#define C_BLUE "\033[34m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"

  static void print_token(const core::LangData &data, const interpreter::core::Token &token) {

    std::string kind = "[UnknownKind]";
    std::string group = "[UnknownGroup]";

    if (token.descriptor) {
      kind = get_kind(token.descriptor->kind);
      group = get_group(token.descriptor->group);
    }

    const std::string text = data.buffer.u32_to_u8(token.span);

    interpreter::debug::Console::debug(C_BLUE, "Token", C_RESET, " {\n", "  ", C_GREEN, "Kind", C_RESET, ": ", kind, "\n", "  ", C_GREEN, "Group", C_RESET, ": ", group, "\n", "  ", C_YELLOW, "Text",
                                       C_RESET, ": \"", text, "\"\n", "  Line: ", token.span.line, " | Start: ", token.span.column, " | End: ", token.span.end_column, "\n", "}");
  }
};
} // namespace interpreter::debug