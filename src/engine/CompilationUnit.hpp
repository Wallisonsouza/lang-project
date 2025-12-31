#pragma once
#include "core/AST.hpp"
#include "core/source/Source.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "language/LanguageSpec.hpp"

struct CompilationUnit {
  ayla::language::LanguageSpec &context;
  core::source::Source &source;

  AST ast;
  core::token::TokenStream tokens;

  DiagnosticEngine diagnostics;

  explicit CompilationUnit(ayla::language::LanguageSpec &ctx, core::source::Source &src) : context(ctx), source(src) {}
};
