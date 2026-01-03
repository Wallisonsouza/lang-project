#include "core/source/Source.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/executor/executor.hpp"
#include "engine/lexer/Lexer.hpp"
#include "engine/parser/Parser.hpp"
#include "engine/resolver/Resolver.hpp"
#include "language/BuiltinScope.hpp"
#include "language/LanguageSpec.hpp"
#include "language/argon_main.hpp"
#include "language/module_console.hpp"
int main() {

  core::source::Source source(
      "/home/wallison/Documentos/git/ayla/src/examples/test.orb");

  auto context = ayla::language::make_lang_context();

  ayla::modules::create_module_console(context.module_manager);

  auto unit = CompilationUnit(context, source);

  lexer::Lexer lexer;
  lexer.generate_tokens(unit);
  debug::engine::dump_tokens(unit.tokens);

  // debug::Console::log("text: ", utils::Utf::utf32to8(source.buffer.view()));

  parser::Parser parser;
  parser.generate_ast(unit);

  ayla::make_ayla_std(context.root_scope);

  for (auto &node : unit.ast.get_nodes()) {
    debug::node::debug_node(node, "", true);
    std::cout << std::endl;
  }

  resolver::Resolver resolver(&context.root_scope);
  resolver.diag_target = &unit.diagnostics;
  resolver.resolve_ast(unit);

  Executor executor{&context.root_scope};
  for (auto &node : unit.ast.get_nodes()) {
    executor.execute(node);
  }

  // optimazer::optimize_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);

  // resolver::Resolver resolver(builtin_scope.get_scope());

  // resolver.resolve_ast(unit.ast);

  return 0;
}