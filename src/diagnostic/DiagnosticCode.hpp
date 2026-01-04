#pragma once

enum class DiagnosticCode {
  ModuleNotFound,
  ExpectedToken,
  InvalidExpressionStatement,
  UndeclaredIdentifier,
  ExpectedExpression,
  ExpectedType,
  InvalidAssignment,
  UnexpectedToken,
  UnterminatedString,
  UndeclaredSymbol,
  NotCallable
};