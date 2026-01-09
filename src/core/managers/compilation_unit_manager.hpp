#pragma once
#include "core/memory/Arena.hpp"
#include "engine/CompilationUnit.hpp"

class CompilationUnitManager {
  core::memory::Arena arena;

public:
  CompilationUnit *create_compilation_unit(LanguageContext &ctx, core::source::Source &src) { return arena.alloc<CompilationUnit>(ctx, src); }
};
