#include "Diagnostic.hpp"
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace core::diagnostics {
class DiagnosticEngine {
private:
  std::vector<Diagnostic> diagnostics;

public:
  // Reporta um novo diagnóstico
  void report(const std::string &message, const std::string &file, int line,
              int column,
              diagnostics::Severity severity = diagnostics::Severity::Error,
              diagnostics::Category category = diagnostics::Category::Parser) {
    diagnostics.emplace_back(message, file, line, column, severity, category);
  }

  // Retorna todos os diagnósticos
  const std::vector<Diagnostic> &get_all() const { return diagnostics; }

  // Filtra diagnósticos por categoria ou severidade
  std::vector<Diagnostic>
  filter(std::function<bool(const Diagnostic &)> predicate) const {
    std::vector<Diagnostic> result;
    for (const auto &d : diagnostics) {
      if (predicate(d))
        result.push_back(d);
    }
    return result;
  }

  // Verifica se existem erros
  bool has_errors() const {
    return std::any_of(diagnostics.begin(), diagnostics.end(),
                       [](const Diagnostic &d) {
                         return d.severity == diagnostics::Severity::Error;
                       });
  }

  // Limpa todos os diagnósticos
  void clear() { diagnostics.clear(); }
};
} // namespace core::diagnostics
