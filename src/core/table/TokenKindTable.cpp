#include "core/table/TokenKindTable.hpp"
#include "core/token/TokenKind.hpp"

namespace lang::debug {

const std::unordered_map<lang::core::TokenKind, const char *> lang::debug::TokenKindTable::kind_map = {
    {lang::core::TokenKind::Function, "Function"},
    {lang::core::TokenKind::If, "If"},
    {lang::core::TokenKind::Equals, "Equals"},
    {lang::core::TokenKind::Ternary, "Ternary"},
    {lang::core::TokenKind::Space, "Space"},
    {lang::core::TokenKind::Variable, "Variable"},
    {lang::core::TokenKind::Colon, "Colon"},
    {lang::core::TokenKind::DoubleQuote, "DoubleQuote"},
    {lang::core::TokenKind::SingleQuote, "SingleQuote"},
    {lang::core::TokenKind::Comma, "Comma"},
    {lang::core::TokenKind::Else, "Else"},
    {lang::core::TokenKind::While, "While"},
    {lang::core::TokenKind::For, "For"},
    {lang::core::TokenKind::Return, "Return"},
    {lang::core::TokenKind::Plus, "Plus"},
    {lang::core::TokenKind::Minus, "Minus"},
    {lang::core::TokenKind::Star, "Star"},
    {lang::core::TokenKind::Slash, "Slash"},
    {lang::core::TokenKind::Assign, "Assign"},
    {lang::core::TokenKind::LParen, "LParen"},
    {lang::core::TokenKind::RParen, "RParen"},
    {lang::core::TokenKind::LBrace, "LBrace"},
    {lang::core::TokenKind::RBrace, "RBrace"},
    {lang::core::TokenKind::Semicolon, "Semicolon"},
    {lang::core::TokenKind::Identifier, "Identifier"},
    {lang::core::TokenKind::Number, "Number"},
    {lang::core::TokenKind::String, "String"},
    {lang::core::TokenKind::EndOfFile, "EndOfFile"},
};

}