#pragma once

#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "diagnostic/DiagnosticCode.hpp"

struct Diagnostic {
  DiagnosticCode code;
  Slice where;

  struct {
    core::token::TokenKind found;
    core::token::TokenKind expected;
  } token;
};
