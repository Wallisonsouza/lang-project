#pragma once
#include "core/AST.hpp"
#include "core/TokenStream.hpp"
#include "core/source/Source.hpp"
#include "language/LanguageSpec.hpp"

struct CompilationUnit {
  ayla::language::LanguageSpec &context;
  core::source::Source &source;

  AST ast;
  TokenStream tokens;

  explicit CompilationUnit(ayla::language::LanguageSpec &ctx,
                           core::source::Source &src)
      : context(ctx), source(src) {}
};
