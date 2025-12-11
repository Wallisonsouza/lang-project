#include <algorithm>
#include <functional>
#include <string>
#include <vector>

namespace interpreter::core {
struct Diagnostic {
  enum class Severity { Error, Warning, Note };
  enum class Category { Lexer, Parser, Semantic };

  std::string message;
  std::string file;
  int line;
  int column;
  Severity severity;
  Category category;

  Diagnostic(const std::string &msg, const std::string &f, int l, int c, Severity s = Severity::Error, Category cat = Category::Parser)
      : message(msg), file(f), line(l), column(c), severity(s), category(cat) {}
};

class DiagnosticEngine {
private:
  std::vector<Diagnostic> diagnostics;

public:
  // Reporta um novo diagnóstico
  void report(const std::string &message,
              const std::string &file,
              int line,
              int column,
              Diagnostic::Severity severity = Diagnostic::Severity::Error,
              Diagnostic::Category category = Diagnostic::Category::Parser) {
    diagnostics.emplace_back(message, file, line, column, severity, category);
  }

  // Retorna todos os diagnósticos
  const std::vector<Diagnostic> &get_all() const { return diagnostics; }

  // Filtra diagnósticos por categoria ou severidade
  std::vector<Diagnostic> filter(std::function<bool(const Diagnostic &)> predicate) const {
    std::vector<Diagnostic> result;
    for (const auto &d : diagnostics) {
      if (predicate(d)) result.push_back(d);
    }
    return result;
  }

  // Verifica se existem erros
  bool has_errors() const {
    return std::any_of(diagnostics.begin(), diagnostics.end(), [](const Diagnostic &d) { return d.severity == Diagnostic::Severity::Error; });
  }

  // Limpa todos os diagnósticos
  void clear() { diagnostics.clear(); }
};

} // namespace interpreter::core
