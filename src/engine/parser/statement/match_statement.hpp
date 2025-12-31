#pragma once
#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/ExpressionParser.hpp"
#include "engine/parser/match/match_return_statement.hpp"
#include "engine/parser/match/match_variable_declaration.hpp"

namespace parser::match {

inline core::node::StatementNode *match_statement(CompilationUnit &unit, core::token::TokenStream &stream, ExpressionParser &exp) {

  auto tok = stream.peek();

  if (!tok || !tok->descriptor) { return nullptr; }

  switch (tok->descriptor->kind) {
  case core::token::TokenKind::ReturnKeyword: return match_return_statement(unit, stream, exp);
  case core::token::TokenKind::Value: return match_variable_declaration(unit, stream, exp);

  default: return nullptr;
  }
}
} // namespace parser::match
