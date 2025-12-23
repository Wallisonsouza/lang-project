#include "core/token/TokenKind.hpp"
#include <string>
#include <unordered_map>

namespace debug::token {

inline const std::unordered_map<core::token::TokenKind, const std::string>
    kind_map = {
        {core::token::TokenKind::UseKeyword, "UseKeyword"},
        {core::token::TokenKind::Dot, "Dot"},
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
        {core::token::TokenKind::OpenParen, "LParen"},
        {core::token::TokenKind::CloseParen, "RParen"},
        {core::token::TokenKind::OpenBrace, "LBrace"},
        {core::token::TokenKind::CloseBrace, "RBrace"},
        {core::token::TokenKind::Semicolon, "Semicolon"},
        {core::token::TokenKind::Identifier, "Identifier"},
        {core::token::TokenKind::NumberLiteral, "NumberLiteral"},
        {core::token::TokenKind::StringLiteral, "StringLiteral"},
        {core::token::TokenKind::EndOfFile, "EndOfFile"},
};

inline const std::string token_kind_to_str(core::token::TokenKind kin) {
  auto it = kind_map.find(kin);
  if (it != kind_map.end())
    return std::string(it->second);
  return "[UnknownKind]";
}
} // namespace debug::token