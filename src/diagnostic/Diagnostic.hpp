#pragma once

#include "core/token/Location.hpp"
#include "diagnostic/diagnostic_code.hpp"
#include "diagnostic/diagnostic_context.hpp"
#include <optional>

enum class DiagnosticOrigin { Lexer, Parser, Semantic, Runtime, Custom };

enum class Severity { Info, Warning, Error, Fatal };

struct Diagnostic {
  DiagnosticOrigin origin;
  DiagnosticCode code;
  Severity severity;

  std::optional<Slice> slice;
  DiagnosticContext context;
};
