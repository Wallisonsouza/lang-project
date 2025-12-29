#include "core/token/Location.hpp"
#include "diagnostic/DiagnosticCode.hpp"

struct Diagnostic {
  DiagnosticCode code;
  Slice slice;
};