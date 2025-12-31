#pragma once

enum class DiagnosticCode {
  ExpectedColon,
  ExpectedToken,
  ExpectedExpression,
  ExpectedType,
  UnexpectedToken,
  UnterminatedString,
  UndeclaredSymbol,
};