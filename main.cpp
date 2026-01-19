#include "core/managers/execution_unit_manager.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "diagnostic/formatter.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/Engine.hpp"
#include "engine/runtime/executor.hpp"
#include "httplib.h"
#include "language/argon_main.hpp"
#include <iostream>
#include <ostream>
#include <string>

#include "core/JsonWriter.hpp"

void lang_server(ExecutionUnit *exec) {
  httplib::Server server;

  std::ostringstream out;
  JsonWriter w(out);

  w.begin_array();

  for (auto &tok : exec->comp_unit.tokens.get_tokens()) {
    w.begin_object();
    w.key("kind");
    w.string(debug::engine::token_kind_to_str(tok->descriptor->kind));

    w.key("lexeme");
    w.string(exec->comp_unit.source.buffer.get_text(tok->slice.span));

    w.key("line");
    w.number(tok->slice.range.begin.line);

    w.key("column");
    w.number(tok->slice.range.begin.column);
    w.end_object();
  }

  w.end_array();

  server.Options(".*", [](const httplib::Request &, httplib::Response &res) {
    res.set_header("Access-Control-Allow-Origin", "*");
    res.set_header("Access-Control-Allow-Methods", "GET, OPTIONS");
    res.set_header("Access-Control-Allow-Headers", "Content-Type");
    res.status = 204;
  });

  server.Get("/tokens",
             [&out](const httplib::Request &, httplib::Response &res) {
               res.set_header("Access-Control-Allow-Origin", "*");
               res.set_content(out.str(), "application/json");
             });

  server.listen("127.0.0.1", 8080);
}

int main() {

  std::vector<std::string> scripts = {
      "/home/wallison/Documentos/git/ayla/examples/stdlib/stdlib.ayla"};

  auto context = ayla::language::create_context();

  auto engine = Engine(context);

  auto exec = engine.create_execution(
      "/home/wallison/Documentos/git/ayla/example.ayla");

  exec->execute();

  std::cout << "ast size: " << exec->comp_unit.ast.size() << std::endl;

  // RuntimeScope scope;
  // Executor executor(&scope);
  // executor.execute_ast(exec->comp_unit);

  for (auto &diag : exec->comp_unit.diagns.all()) {
    print(*diag, exec->comp_unit);
  }

  return 0;
}
