#include "core/managers/execution_unit_manager.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/Engine.hpp"
#include "engine/runtime/executor.hpp"
#include "language/argon_main.hpp"
#include <string>

int main() {

  auto context = ayla::language::create_context();

  auto engine = Engine(context);

  auto exec = engine.create_execution("/home/wallison/Documentos/git/ayla/src/examples/test.orb");

  exec->execute();

  debug::engine::dump_tokens(exec->comp_unit.tokens);
  debug::node::dump_ast(exec->comp_unit.ast);

  RuntimeScope scope;
  Executor executor(&scope);
  executor.execute_ast(exec->comp_unit);

  return 0;
}
