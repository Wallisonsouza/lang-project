#pragma once
#include <cstdint>

namespace interpreter::core {
enum class TokenKind : uint8_t {
  Function,
  If,
  Else,
  While,
  For,
  Return,
  Comma,
  DoubleQuote,
  SingleQuote,
  Variable,
  Colon,

  Plus,
  Minus,
  Star,
  Slash,
  Assign,
  Equals,
  Ternary,

  LParen,
  Space,
  RParen,
  LBrace,
  RBrace,
  Semicolon,

  NumberType,
  StringType,

  Identifier,
  NumberLiteral,
  StringLiteral,
  NullLiteral,
  CharLiteral,
  BoolLiteral,
  EndOfFile,
};
}
