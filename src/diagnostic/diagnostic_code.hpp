#pragma once

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
  RedeclaredIdentifier,
  IfBlockError,

  // if
  IfConditionMissing,
  IfConditionAssignment,
  ThenBlockMissing,
  ElseBlockMissing
};
