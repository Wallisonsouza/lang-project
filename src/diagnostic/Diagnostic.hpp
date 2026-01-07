#pragma once
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include <optional>
#include <string>

enum class DiagnosticCode {
  UnexpectedToken,
  ExpectedToken,
  ExpectedIdentifier,
  ExpectedType,
  ExpectedExpression,
  ExpectedColon,
  ExpectedDoubleColon,
  UndeclaredSymbol,
  NotCallable,
  UnterminatedString,
  ModuleNotFound,
  Custom
};

enum class DiagnosticOrigin { Lexer, Parser, Semantic, Runtime, Custom };

struct DiagnosticToken {
  core::token::TokenKind expected;
  const core::token::Token *found;
};

struct Diagnostic {
  DiagnosticCode code;
  DiagnosticOrigin origin;
  std::optional<Slice> slice;
  std::optional<std::string> message;
  std::optional<std::string> suggestion;
  std::optional<DiagnosticToken> token;
  std::string file;
};
