#pragma once
#include "core/AST.hpp"
#include "core/Context.hpp"

#include "core/Error.hpp"
#include "core/TokenStream.hpp"
#include "core/table/AliasTable.hpp"
#include "core/text/Source.hpp"

struct CompilationUnit {
  core::Context &context;
  core::source::Source source;

  AST ast;
  TokenStream tokens;

  core::error::ErrorEngine engine;

  core::table::AliasTable alias_table{context.descriptor_table};

  explicit CompilationUnit(core::Context &ctx, core::source::Source src) : context(ctx), source(std::move(src)) {}
};
