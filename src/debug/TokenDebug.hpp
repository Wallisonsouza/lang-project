#pragma once
#include "core/LangData.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "debug/Console.hpp"
#include "utils/Utf8.hpp"
#include <string>
#include <unordered_map>

namespace debug {
class TokenDebug {

private:
  inline static const std::unordered_map<core::token::TokenGroup,
                                         const std::string>
      group_map = {
          {core::token::TokenGroup::Name, "Name"},
          {core::token::TokenGroup::Keyword, "Keyword"},
          {core::token::TokenGroup::Operator, "Operator"},
          {core::token::TokenGroup::Punctuation, "Punctuation"},
          {core::token::TokenGroup::Literal, "Literal"},
          {core::token::TokenGroup::Type, "Type"},
          {core::token::TokenGroup::Error, "Error"},
  };

  inline static const std::unordered_map<core::token::TokenKind,
                                         const std::string>
      kind_map = {
          {core::token::TokenKind::NumberType, "NumberType"},
          {core::token::TokenKind::StringType, "StringType"},
          {core::token::TokenKind::Function, "Function"},
          {core::token::TokenKind::If, "If"},
          {core::token::TokenKind::Equals, "Equals"},
          {core::token::TokenKind::Ternary, "Ternary"},
          {core::token::TokenKind::Space, "Space"},
          {core::token::TokenKind::Variable, "Variable"},
          {core::token::TokenKind::Colon, "Colon"},
          {core::token::TokenKind::DoubleQuote, "DoubleQuote"},
          {core::token::TokenKind::SingleQuote, "SingleQuote"},
          {core::token::TokenKind::Comma, "Comma"},
          {core::token::TokenKind::Else, "Else"},
          {core::token::TokenKind::While, "While"},
          {core::token::TokenKind::For, "For"},
          {core::token::TokenKind::Return, "Return"},
          {core::token::TokenKind::Plus, "Plus"},
          {core::token::TokenKind::Minus, "Minus"},
          {core::token::TokenKind::Star, "Star"},
          {core::token::TokenKind::Slash, "Slash"},
          {core::token::TokenKind::Assign, "Assign"},
          {core::token::TokenKind::LParen, "LParen"},
          {core::token::TokenKind::RParen, "RParen"},
          {core::token::TokenKind::LBrace, "LBrace"},
          {core::token::TokenKind::RBrace, "RBrace"},
          {core::token::TokenKind::Semicolon, "Semicolon"},
          {core::token::TokenKind::Identifier, "Identifier"},
          {core::token::TokenKind::NumberLiteral, "NumberLiteral"},
          {core::token::TokenKind::StringLiteral, "StringLiteral"},
          {core::token::TokenKind::EndOfFile, "EndOfFile"},
  };

  static const std::string get_kind(core::token::TokenKind kin) {
    auto it = kind_map.find(kin);
    if (it != kind_map.end())
      return std::string(it->second);
    return "[UnknownKind]";
  }

  static const std::string get_group(core::token::TokenGroup grp) {
    auto it = group_map.find(grp);
    if (it != group_map.end())
      return std::string(it->second);
    return "[UnknownGroup]";
  }

public:
#define C_RESET "\033[0m"
#define C_BLUE "\033[34m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"

  static void print_token(const core::LangData &data,
                          const core::token::Token &token) {

    std::string kind = "[UnknownKind]";
    std::string group = "[UnknownGroup]";

    if (token.descriptor) {
      kind = get_kind(token.descriptor->kind);
      group = get_group(token.descriptor->group);
    }

    auto &span = token.span;
    const auto &buffer = data.buffer;
    std::u32string_view view(buffer.u32().data() + span.start, span.length());

    const std::string text = utils::Utf::utf32to8(view);

    Console::debug(C_BLUE, "Token", C_RESET, " {\n", "  ", C_GREEN, "Kind",
                   C_RESET, ": ", kind, "\n", "  ", C_GREEN, "Group", C_RESET,
                   ": ", group, "\n", "  ", C_YELLOW, "Text", C_RESET, ": \"",
                   text, "\"\n", "  Line: ", token.span.line,
                   " | Start: ", token.span.column,
                   " | End: ", token.span.end_column, "\n", "}");
  }
};
} // namespace debug