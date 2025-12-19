#pragma once

#include "core/token/Location.hpp"
#include <string>
#include <vector>

namespace core::diagnostics {
enum class DiagnosticLevel { Error, Warning, Note };

struct Diagnostic {
  DiagnosticLevel level;
  std::string message;
  SourceRange range;
  std::vector<std::string> hints;
};

} // namespace core::diagnostics