#pragma once
#include "core/AST.hpp"
#include "core/memory/symbol_manager.hpp"
#include "core/source/Source.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include "engine/language_context.hpp"
#include "engine/lexer/lexer.hpp"

struct CompilationUnit {
  LanguageContext &context;
  core::source::Source &source;

  SymbolManager symbols;
  DiagnosticEngine diagns;

  AST ast;
  core::token::TokenStream tokens;

  Lexer lexer;

  void exec() { lexer.generate_tokens(context, source.buffer, tokens); }

  explicit CompilationUnit(LanguageContext &ctx, core::source::Source &src) : context(ctx), source(src), diagns(*this) {}
};
