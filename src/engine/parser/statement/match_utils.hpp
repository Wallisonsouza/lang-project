#pragma once
#include "core/node/Type.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/expression/parse_expression.hpp"
#include "engine/parser/statement/match_type.hpp"

inline bool expect_token(CompilationUnit &unit, core::token::TokenStream &stream, core::token::TokenKind expected) {

  if (stream.match(expected)) return true;

  const auto *tok = stream.peek();
  const auto found = tok ? tok->descriptor->kind : core::token::TokenKind::EndOfFile;

  const Slice &where = tok ? tok->slice : stream.last_slice();

  // unit.diagnostics.expected_token(where, expected, found);
  return false;
}

inline core::node::TypeNode *expect_type(CompilationUnit &unit, core::token::TokenStream &stream) {

  if (auto *type = parser::statement::parse_type(unit, stream)) return type;

  const auto *tok = stream.peek();
  const auto found = tok ? tok->descriptor->kind : core::token::TokenKind::EndOfFile;

  const Slice &where = tok ? tok->slice : stream.last_slice();

  // unit.diagnostics.expected_type(where, found);
  return nullptr;
}

inline core::node::ExpressionNode *expect_expression(CompilationUnit &unit, core::token::TokenStream &stream) {

  if (auto *expr = parser::expression::parse_expression(unit, stream)) return expr;

  const auto *tok = stream.peek();
  const auto found = tok ? tok->descriptor->kind : core::token::TokenKind::EndOfFile;

  const Slice &where = tok ? tok->slice : stream.last_slice();

  // unit.diagnostics.expected_expression(where, found);
  return nullptr;
}
