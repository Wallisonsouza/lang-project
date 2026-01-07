// #include "DiagnosticEngine.hpp"
// #include "core/token/TokenKind.hpp"
// #include "debug/engine/token/dump_tokens.hpp"
// #include "diagnostic/Diagnostic.hpp"
// #include "diagnostic/DiagnosticCode.hpp"
// #include "diagnostic/diagnostic_debug.hpp"
// #include "engine/CompilationUnit.hpp"
// #include <string>

// void DiagnosticEngine::emit(const DiagnosticCode code, const core::token::TokenKind expected, const core::token::Token found) {
//   std::string text;
//   std::string help;

//   Diagnostic diag{.code = code, .token{.found = found, .expected = expected}};

//   switch (diag.code) {
//   case DiagnosticCode::UnexpectedToken: {
//     // Pega o token esperado e encontrado
//     auto expected_desc = unit.context.descriptor_table.lookup_by_kind(diag.token.expected);
//     auto found_slice = diag.token.found->slice;

//     // Mensagem de erro principal
//     text = "Unexpected token: ";
//     if (diag.token.found) {
//       text += unit.source.buffer.get_text(found_slice.span); // mostra exatamente o que foi digitado
//     } else {
//       text += "<eof>";
//     }

//     // Sugestão de correção
//     help = "Remove '";
//     help += unit.source.buffer.get_text(found_slice.span);
//     help += "' and add '";
//     help += expected_desc->name;
//     help += "'";

//     // Adiciona aliases do token esperado, se houver
//     if (!expected_desc->aliases.empty()) {
//       help += " (aliases: ";
//       for (size_t i = 0; i < expected_desc->aliases.size(); ++i) {
//         help += expected_desc->aliases[i];
//         if (i + 1 < expected_desc->aliases.size()) help += " | ";
//       }
//       help += ")";
//     }

//     break;
//   }

//   case DiagnosticCode::NotCallable:
//     text = "NotCallable:";
//     help = " this value is not callable";
//     break;

//   case DiagnosticCode::UndeclaredSymbol:
//     text = "UndeclaredSymbol:";
//     help = " the symbol '";

//     help += diag.where.span.view();
//     help += "' is not declared";
//     break;

//   case DiagnosticCode::UnterminatedString:
//     text = "UnterminatedString:";
//     help = "add \" on string end";
//     break;

//   case DiagnosticCode::ModuleNotFound:
//     text = "ModuleNotFound:";
//     help = " the specified module could not be found";
//     break;

//   case DiagnosticCode::ExpectedIdentifier:
//     text = "Expected identifier:";
//     help = "You must provide a variable or function name here";
//     break;

//   case DiagnosticCode::ExpectedExpression:
//     text = "Expected expression:";
//     help = "An expression (value, function call, etc.) is required here";
//     break;

//   case DiagnosticCode::ExpectedType:
//     text = "Expected type:";
//     help = "Specify a type after the ':' (e.g., Number, String, etc.)";
//     break;

//   case DiagnosticCode::ExpectedColon:
//     text = "Expected ':'";
//     help = "Add a ':' before the type declaration";
//     break;

//   case DiagnosticCode::ExpectedToken: {
//     // Pega o token esperado
//     auto expected_desc = unit.context.descriptor_table.lookup_by_kind(diag.token.expected);

//     text = "Expected ";
//     text += expected_desc->name;

//     // Sugestão de correção
//     help = "add '" + expected_desc->name + "'";

//     // Se houver um token encontrado, podemos apontar e sugerir remover/substituir
//     if (diag.token.found) {
//       auto found_text = unit.source.buffer.get_text(diag.token.found->slice.span);
//       help = "Remove '" + found_text + "' and add '" + expected_desc->name + "'";
//     }

//     // Se houver aliases para o token esperado
//     if (!expected_desc->aliases.empty()) {
//       help += " (aliases: ";
//       for (size_t i = 0; i < expected_desc->aliases.size(); ++i) {
//         help += expected_desc->aliases[i];
//         if (i + 1 < expected_desc->aliases.size()) help += " | ";
//       }
//       help += ")";
//     }

//     break;
//   }

//   default:
//     text = "Error:";
//     help = "";
//     break;
//   }

//   diagnostic::print_diagnostic(text, help, diag.where, unit.source.buffer);
// }
