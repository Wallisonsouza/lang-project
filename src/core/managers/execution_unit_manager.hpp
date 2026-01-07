#pragma once
#include "core/memory/Arena.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/ExecutionUnit.hpp"

class ExecutionUnitManager {
  core::memory::Arena arena;

public:
  ExecutionUnit *create_execution_unit(CompilationUnit &cu) { return arena.create<ExecutionUnit>(cu); }
};
