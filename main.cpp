#include "core/source/Source.hpp"
#include "core/source/TextStream.hpp"
#include "core/token/token_stream.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/lexer/lexer.hpp"
#include "engine/parser/parser.hpp"
#include "engine/resolver/Resolver.hpp"
#include "engine/runtime/executor.hpp"
#include "language/argon_main.hpp"
#include "language/module_console.hpp"

int main() {

  core::source::Source source("/home/wallison/Documentos/git/ayla/src/examples/test.orb");

  auto context = ayla::language::make_lang_context();

  auto parent = context.modules.create_module("debug");
  ayla::modules::create_module_console(context, parent);
  ayla::modules::create_module_math(context);
  
  auto unit = CompilationUnit(context, source);

  Lexer lexer(unit);
  lexer.generate_tokens();

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

  // for (auto &node : unit.ast.get_nodes()) {
  //   debug::node::debug_node(node, "", true);
  //   std::cout << std::endl;
  // }

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