#include "DiagnosticEngine.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "diagnostic/diagnostic_debug.hpp"
#include <iostream>

void DiagnosticEngine::emit(const Diagnostic diag, const core::source::SourceBuffer &buffer) {

  std::string text;

  switch (diag.code) {
  case DiagnosticCode::NotCallable: text = "NotCallable: "; break;
  case DiagnosticCode::UndeclaredSymbol: text = "UndeclaredSymbol: "; break;
  case DiagnosticCode::ModuleNotFound: text = "ModuleNotFound: "; break;
  case DiagnosticCode::ExpectedColon: text = "ExpectedColon: "; break;
  default: break;
  }

  diagnostic::print_diagnostic(text, diag.where, buffer);
}

void DiagnosticEngine::expected_token(const Slice &where, core::token::TokenKind expected, core::token::TokenKind found) {
  // emit({.code = DiagnosticCode::ExpectedToken, .where = where, .token = {found, expected}});
}

void DiagnosticEngine::expected_type(const Slice &where, core::token::TokenKind found) {
  // emit({.code = DiagnosticCode::ExpectedType, .where = where, .token = {found, core::token::TokenKind::Invalid}});
}
// void DiagnosticEngine::expected_expression(const Slice &where, core::token::TokenKind found) { emit(Diagnostic{DiagnosticCode::ExpectedExpression, where, core::token::TokenKind::Invalid, found}); }
