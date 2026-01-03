#pragma once
#include "core/token/TokenKind.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/declaration/parse_variable_declaration.hpp"
#include "engine/parser/statement/match_import_statement.hpp"

#pragma once
#include "engine/CompilationUnit.hpp"

namespace parser::statement {

inline core::node::Node *parse_statement(CompilationUnit &unit,
                                         core::token::TokenStream &stream) {
  stream.add_checkpoint();

  core::node::Node *result = nullptr;

  auto *tok = stream.peek();
  if (!tok)
    return nullptr;

  if (auto *import_stmt = match_import_statement(unit, stream)) {
    result = import_stmt;
  }
  // 2️⃣ DECLARAÇÕES
  else if (tok->descriptor->kind == core::token::TokenKind::Value ||
           tok->descriptor->kind == core::token::TokenKind::Variable) {
    result = parser::declaration::parse_variable_declaration(unit, stream);
  } else if (tok->descriptor->kind == core::token::TokenKind::FunctionKeyword) {
    // result = parser::declaration::parse_function_declaration(unit, stream);
  }
  // 3️⃣ EXPRESSÃO (fallback)
  else {
    auto *expr = parser::expression::parse_expression(unit, stream);
    if (!expr) {
      stream.rollback_checkpoint();
      return nullptr;
    }
    result = expr;
  }

  if (!result) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  // 4️⃣ Final de statement
  tok = stream.peek();

  if (tok && tok->descriptor->kind == core::token::TokenKind::Semicolon) {
    stream.consume();
  } else {
    unit.diagnostics.emit(
        {DiagnosticCode::ExpectedToken,
         stream.last_slice(),
         {.found = tok, .expected = core::token::TokenKind::Semicolon}},
        unit);
  }

  stream.discard_checkpoint();
  return result;
}

} // namespace parser::statement
