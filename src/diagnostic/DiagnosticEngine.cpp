#include "DiagnosticEngine.hpp"

void DiagnosticEngine::emit(const Diagnostic diag) {
  // Aqui você decide:
  // - armazenar
  // - imprimir
  // - agrupar
  // - abortar compilação
}

void DiagnosticEngine::expected_token(const Slice &where, core::token::TokenKind expected, core::token::TokenKind found) {
  emit({.code = DiagnosticCode::ExpectedToken, .where = where, .token = {found, expected}});
}

void DiagnosticEngine::expected_type(const Slice &where, core::token::TokenKind found) {
  emit({.code = DiagnosticCode::ExpectedType, .where = where, .token = {found, core::token::TokenKind::Invalid}});
}
void DiagnosticEngine::expected_expression(const Slice &where, core::token::TokenKind found) { emit(Diagnostic{DiagnosticCode::ExpectedExpression, where, core::token::TokenKind::Invalid, found}); }
