#pragma once

enum class DiagnosticCode {
  ModuleNotFound,
  ExpectedToken,
  UndeclaredIdentifier,
  ExpectedExpression,
  ExpectedType,
  UnexpectedToken,
  UnterminatedString,
  UndeclaredSymbol,
  NotCallable
};