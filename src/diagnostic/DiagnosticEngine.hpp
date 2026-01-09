#pragma once
#include "Diagnostic.hpp"

#include <vector>

struct CompilationUnit;
class DiagnosticEngine {
  const CompilationUnit &unit;

  std::vector<Diagnostic> diagnostics;

public:
  explicit DiagnosticEngine(const CompilationUnit &unit) : unit(unit) {}
  void report(const Diagnostic &e) { diagnostics.push_back(e); }
  const std::vector<Diagnostic> &all() const { return diagnostics; }
};
