#include "core/module/ModuleRegistry.hpp"
#include "core/source/Source.hpp"
#include "debug/console/console.hpp"
#include "debug/node/debug_print_node.hpp"
#include "debug/token/debug_token.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/lexer/Lexer.hpp"
#include "engine/parser/Parser.hpp"
#include "language/argon_main.hpp"

int main() {

  core::source::Source source(
      "/home/wallison/Documentos/git/ayla/src/examples/test.orb");

  auto context = ayla::language::make_lang_context();

  context.alias_table.build();

  auto unit = CompilationUnit(context, source);

  lexer::Lexer lexer;
  lexer.generate_tokens(unit);
  for (auto &tok : unit.tokens.get_tokens()) {
    debug::token::print_token(unit, tok);
  }

  auto module = context.module_registry.get_or_create(U"std::console", nullptr);

  parser::Parser parser;
  parser.generate_ast(unit);

  debug::Console::log(unit.ast.size());
  for (auto &node : unit.ast.get_nodes()) {
    debug::node::print_node(node);
  }

  // optimazer::optimize_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);

  // resolver::Resolver resolver(builtin_scope.get_scope());

  // resolver.resolve_ast(unit.ast);

  // unit.engine.print_all_errors(unit.alias_table);

  return 0;
}
