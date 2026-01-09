#include "diagnostic/formatter.hpp"
#include "diagnostic/diagnostic_debug.hpp"
#include "diagnostic/diagnostics_table.hpp"
#include <variant>

struct DiagnosticValueRenderer {
  const CompilationUnit &unit;

  std::string operator()(const std::string &s) const { return s; }

  std::string operator()(core::token::TokenKind k) const { return "'" + unit.context.descriptor_table.lookup_by_kind(k)->name + "'"; }

  std::string operator()(core::node::NodeKind k) const { return "unit.context.node_names.at(k);"; }
};

std::string render_value(const DiagnosticValue &v, const CompilationUnit &unit) { return std::visit(DiagnosticValueRenderer{unit}, v); }

std::string apply_template(const std::string &tmpl, const DiagnosticContext &ctx, const CompilationUnit &unit) {
  std::string out;

  for (size_t i = 0; i < tmpl.size(); ++i) {
    if (tmpl[i] == '{') {
      auto end = tmpl.find('}', i);
      if (end != std::string::npos) {
        auto key = tmpl.substr(i + 1, end - i - 1);
        if (auto *val = ctx.get(key)) {
          out += render_value(*val, unit);
        } else {
          out += "{" + key + "}";
        }
        i = end;
        continue;
      }
    }
    out += tmpl[i];
  }

  return out;
}

void print(const Diagnostic &diag, const CompilationUnit &unit) {

  auto it = DIAG_PT_BR.find(diag.code);
  if (it == DIAG_PT_BR.end()) {
    std::cerr << "Erro desconhecido\n";
    return;
  }

  const auto &tmpl = it->second;

  // Mensagem
  std::string message = apply_template(tmpl.message, diag.context, unit);

  diagnostic::print_diagnostic(tmpl.title, message, "", diag.slice.value_or({}), unit.source.buffer);
}
