#include "DiagnosticEngine.hpp"
#include "core/token/TokenKind.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "diagnostic/diagnostic_debug.hpp"
#include "engine/CompilationUnit.hpp"
#include <string>
void DiagnosticEngine::emit(const Diagnostic diag,
                            const CompilationUnit &unit) {
  std::string text;
  std::string help;

  switch (diag.code) {
  case DiagnosticCode::UnexpectedToken: {
    text = "Unexpected token";

    help = "remove this token or insert a valid one before it";
    break;
  }

  case DiagnosticCode::NotCallable:
    text = "NotCallable:";
    help = " this value is not callable";
    break;

  case DiagnosticCode::UndeclaredSymbol:
    text = "UndeclaredSymbol:";
    help = " the symbol '";

    help += diag.where.span.view();
    help += "' is not declared";
    break;

  case DiagnosticCode::UnterminatedString:
    text = "UnterminatedString:";
    help = "add \" on string end";
    break;

  case DiagnosticCode::ModuleNotFound:
    text = "ModuleNotFound:";
    help = " the specified module could not be found";
    break;

  case DiagnosticCode::ExpectedToken: {
    auto desc =
        unit.context.descriptor_table.lookup_by_kind(diag.token.expected);

    text = "Expected ";
    text += desc->name;

    help = "add '" + desc->name + "'";

    if (!desc->aliases.empty()) {
      help += " (aliases: ";
      for (size_t i = 0; i < desc->aliases.size(); ++i) {
        help += desc->aliases[i];
        if (i + 1 < desc->aliases.size())
          help += " | ";
      }
      help += ")";
    }

    break;
  }

  default:
    text = "Error:";
    help = "";
    break;
  }

  diagnostic::print_diagnostic(text, help, diag.where, unit.source.buffer);
}
