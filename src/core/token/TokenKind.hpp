#pragma once
#include <cstdint>

enum class TokenKind : uint8_t {
  If,
  Else,
  While,
  For,
  Return,

  Plus,
  Minus,
  Star,
  Slash,
  Assign,

  LParen,
  RParen,
  LBrace,
  RBrace,
  Semicolon,

  Identifier,
  Number,
  String,
  EndOfFile,
};