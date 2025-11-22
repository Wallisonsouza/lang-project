#pragma once
#include <cstdint>

namespace lang::core {
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

  Identifier,
  Number,
  String,
  EndOfFile,
};
}
