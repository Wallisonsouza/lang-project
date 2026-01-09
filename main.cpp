#include "core/managers/execution_unit_manager.hpp"
#include "debug/engine/node/ast_debug.hpp"
#include "diagnostic/formatter.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/Engine.hpp"
#include "engine/runtime/executor.hpp"
#include "language/argon_main.hpp"
#include <string>

int main() {

  auto context = ayla::language::create_context();

  auto engine = Engine(context);

  auto exec = engine.create_execution("/home/wallison/Documentos/git/ayla/example.ayla");

  exec->execute();

  auto debugger = ASTDebug();

  debugger.dump_ast(exec->comp_unit.ast);

  RuntimeScope scope;
  Executor executor(&scope);
  executor.execute_ast(exec->comp_unit);

  for (auto &diag : exec->comp_unit.diagns.all()) { print(diag, exec->comp_unit); }

  return 0;
}
