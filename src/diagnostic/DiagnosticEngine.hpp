

#include "core/token/Location.hpp"
#include "diagnostic/Diagnostic.hpp"
#include <vector>
class DiagnosticEngine {
private:
  std::vector<Diagnostic> diagnostics;

public:
  void add_error(DiagnosticCode code, Slice slice) {
    diagnostics.emplace_back(code, slice);
  }
};
