
#include "argon/argon_main.hpp"
#include "core/CompilationUnit.hpp"
#include "core/module/BuiltinScope.hpp"
#include "debug/NodeDebug.hpp"
#include "debug/TokenDebug.hpp"
#include "lexer/Lexer.hpp"
#include "optimizer/Optimizer.hpp"
#include "parser/Parser.hpp"
#include "resolver/Resolver.hpp"
#include "utils/TextLoader.hpp"
#include <iostream>
#include <string>

int main() {

  core::source::Source source(
      "../examples/test.orb",
      utils::TextLoader::load_file("../examples/test.orb"));

  auto context = argon::make_lang_context();

  auto unit = CompilationUnit(context, source);
  unit.alias_table.build();

  lexer::Lexer lexer;
  lexer.generate_tokens(unit);
  // for (auto &tok : unit.tokens.get_tokens()) {
  //   debug::TokenDebug::print_token(unit, tok);
  // }

  parser::Parser parser;
  parser.generate_ast(unit);

  debug::print_ast(unit.ast);
  optimazer::optimize_ast(unit.ast);
  debug::print_ast(unit.ast);

  core::BuiltinScope builtin_scope;
  resolver::Resolver resolver(builtin_scope.get_scope());

  resolver.resolve_ast(unit.ast);

  // unit.engine.print_all_errors(unit.alias_table);

  return 0;
}
