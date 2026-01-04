#include "core/source/Source.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/executor/executor.hpp"
#include "engine/lexer/Lexer.hpp"
#include "engine/parser/parser.hpp"
#include "engine/resolver/Resolver.hpp"
#include "language/BuiltinScope.hpp"
#include "language/LanguageSpec.hpp"
#include "language/argon_main.hpp"
#include "language/module_console.hpp"
#include <iostream>

int main() {

  core::source::Source source("/home/wallison/Documentos/git/ayla/src/examples/test.orb");

  auto context = ayla::language::make_lang_context();

  auto unit = CompilationUnit(context, source);
  ayla::modules::create_module_console(unit);
  lexer::Lexer lexer;
  lexer.generate_tokens(unit);
  // debug::engine::dump_tokens(unit.tokens);
  ayla::make_ayla_std(context.root_scope);

  Parser parser(unit, unit.tokens);

  while (!unit.tokens.is_end()) {
    auto node = parser.parse_statement();
    if (node) {
      unit.ast.add_root(node);
    } else {
      unit.tokens.advance();
    }
  }

  // debug::Console::log("text: ", utils::Utf::utf32to8(source.buffer.view()));

  // parser::Parser parser;
  // parser.generate_ast(unit);

  for (auto &node : unit.ast.get_nodes()) {
    debug::node::debug_node(node, "", true);
    std::cout << std::endl;
  }

  resolver::Resolver resolver(&context.root_scope);
  resolver.diag_target = &unit.diagnostics;
  resolver.resolve_ast(unit);

  RuntimeScope scope;
  Executor executor(&scope);

  for (auto &node : unit.ast.get_nodes()) { executor.execute_node(unit, node); }

  // optimazer::optimize_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);

  // resolver::Resolver resolver(builtin_scope.get_scope());

  // resolver.resolve_ast(unit.ast);

  return 0;
}