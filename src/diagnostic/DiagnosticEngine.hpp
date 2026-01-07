#pragma once
#include "Diagnostic.hpp"
#include <string>
#include <vector>

struct CompilationUnit;
class DiagnosticEngine {
  const CompilationUnit &unit;

  std::vector<Diagnostic> diagnostics;

public:
  explicit DiagnosticEngine(const CompilationUnit &unit) : unit(unit) {}
  void report(const Diagnostic &e) { diagnostics.push_back(e); }
  const std::vector<Diagnostic> &all() const { return diagnostics; }

private:
  std::string suggest_add(core::token::TokenKind expected);
  std::string suggest_remove(const core::token::Token *found, core::token::TokenKind expected);
};
