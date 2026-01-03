#pragma once

#include "core/token/Location.hpp"
#include "core/token/Token.hpp"
#include "core/token/TokenKind.hpp"
#include "diagnostic/DiagnosticCode.hpp"

struct Diagnostic {
  const DiagnosticCode code;
  const Slice where;

  struct {
    const core::token::Token *found;
    core::token::TokenKind expected;
  } token;
};
