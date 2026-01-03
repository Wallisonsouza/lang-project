#pragma once
#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "diagnostic/Diagnostic.hpp"

struct CompilationUnit;
class DiagnosticEngine {
public:
  void expected_token(const Slice &where, core::token::TokenKind expected, core::token::TokenKind found);

  void expected_type(const Slice &where, core::token::TokenKind found);

  void expected_expression(const Slice &where, core::token::TokenKind found);

  void emit(Diagnostic diag, const CompilationUnit &unit);
};
