
#include "argon/argon_main.hpp"
#include "core/AST.hpp"
#include "core/CompilationUnit.hpp"
#include "core/module/BuiltinScope.hpp"
#include "core/module/Scope.hpp"
#include "core/node/Node.hpp"
#include "debug/Console.hpp"
#include "debug/NodeDebug.hpp"
#include "debug/TokenDebug.hpp"
#include "lexer/Lexer.hpp"
#include "parser/Parser.hpp"
#include "utils/TextLoader.hpp"
#include <iostream>
#include <string>

// void traverse_ast(core::node::Node *node, core::Scope &current_scope) {
//   if (!node) return;

//   if (auto var_decl = dynamic_cast<parser::VariableDeclarationNode *>(node)) {
//     traverse_ast(var_decl->type, current_scope);
//     traverse_ast(var_decl->value, current_scope);
//   }
// }

// inline void validate_ast(CompilationUnit &unit, core::Scope &scope) {
//   for (auto node : unit.nodes) {
//     if (auto var = dynamic_cast<parser::VariableDeclarationNode *>(node)) { semantic::validate_variable_declaration(unit, var, scope); }
//     // aqui você pode adicionar outras validações:
//     // funções, structs, expressions, etc.
//   }
// }

int main() {
  core::source::Source source("../examples/test.orb", utils::TextLoader::load_file("../examples/test.orb"));

  auto context = argon::make_lang_context();

  auto unit = CompilationUnit(context, source);
  unit.alias_table.build();

  lexer::Lexer lexer;
  lexer.generate_tokens(unit);

  parser::Parser parser;
  parser.generate_ast(unit);

  debug::Console::log(unit.ast.size());

  for (auto &node : unit.ast.get_nodes()) { debug::print_node(node); }

  // for (auto &tok : unit.tokens.get_tokens()) { debug::TokenDebug::print_token(unit, tok); }

  core::BuiltinScope builtin_scope;

  core::Scope global_scope(&builtin_scope);

  // validate_ast(unit, global_scope);

  unit.engine.print_all_errors(unit.alias_table);

  return 0;
}
