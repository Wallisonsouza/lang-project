#include "core/managers/compilation_unit_manager.hpp"
#include "core/managers/execution_unit_manager.hpp"
#include "core/managers/surce_manager.hpp"
#include "core/memory/Arena.hpp"
#include "core/source/Source.hpp"
#include "core/token/Location.hpp"
#include "core/token/token_stream.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "debug/engine/token/dump_tokens.hpp"
#include "diagnostic/Diagnostic.hpp"
#include "diagnostic/diagnostic_debug.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/language_context.hpp"
#include "engine/lexer/lexer.hpp"
#include "engine/parser/parser.hpp"
#include "language/argon_main.hpp"
#include "language/module_console.hpp"
#include <string>

class Engine {

  LanguageContext &context;

  SourceManager src_manager;
  CompilationUnitManager cu_manage;
  ExecutionUnitManager eu_manager;

public:
  Engine(LanguageContext &context) : context(context) {}

  ExecutionUnit *create_execution(const std::string &path) {

    auto source = src_manager.create_source(path);

    auto compilation = cu_manage.create_compilation_unit(context, *source);

    return eu_manager.create_execution_unit(*compilation);
  }
};

int main() {

  auto context = ayla::language::make_lang_context();

  auto parent = context.modules.create_module("debug");
  ayla::modules::create_module_console(context, parent);
  ayla::modules::create_module_math(context);


  

  auto engine = Engine(context);

  auto exec = engine.create_execution("/home/wallison/Documentos/git/ayla/src/examples/test.orb");

  exec->execute();

  debug::engine::dump_tokens(exec->comp_unit.tokens);
  debug::node::dump_ast(exec->comp_unit.ast);

  // for (auto &diag : unit.diagns.all()) {
  //   std::string help;
  //   Slice slice = diag.slice.value_or(Slice{});

  //   const core::token::Token *found_token = nullptr;
  //   if (diag.token && diag.token->found) {
  //     found_token = diag.token->found;
  //     slice = found_token->slice;
  //   }

  //   switch (diag.code) {

  //   case DiagnosticCode::ExpectedToken: {

  //     auto tok = unit.context.descriptor_table.lookup_by_kind(diag.token->expected);

  //     if (found_token) {
  //       help += "Expected ";
  //       help += "'";
  //       help += tok->name;
  //       help += "'";
  //       help += " but found '" + unit.source.buffer.get_text(found_token->slice.span) + "' ";

  //     } else {
  //       help = "Add an identifier";
  //     }
  //     break;
  //   }

  //     // case DiagnosticCode::ExpectedIdentifier:
  //     //   if (found_token) {
  //     //     help = "Expected 'identifier' but found '" + unit.source.buffer.get_text(found_token->slice.span) + "'";
  //     //   } else {
  //     //     help = "Add an identifier";
  //     //   }
  //     //   break;

  //   case DiagnosticCode::ExpectedColon:
  //     if (found_token) {
  //       help = "Expected ':' but found '" + unit.source.buffer.get_text(found_token->slice.span) + "'";
  //     } else {
  //       help = "Expected ':'";
  //     }
  //     break;

  //   case DiagnosticCode::ExpectedType:
  //     if (found_token) {
  //       help = "Expected a type but found '" + unit.source.buffer.get_text(found_token->slice.span) + "'";
  //     } else {
  //       help = "Expected a type";
  //     }
  //     break;

  //   case DiagnosticCode::ExpectedExpression:
  //     if (found_token) {
  //       help = "Expected an expression but found '" + unit.source.buffer.get_text(found_token->slice.span) + "'";
  //     } else {
  //       help = "Expected an expression";
  //     }
  //     break;

  //   case DiagnosticCode::UnexpectedToken:
  //     if (found_token) {
  //       help = "Unexpected token '" + unit.source.buffer.get_text(found_token->slice.span) + "'";
  //     } else {
  //       help = "Unexpected token";
  //     }
  //     break;

  //   default: help = "Unknown error"; break;
  //   }

  //   // Chama a função de print centralizada
  //   diagnostic::print_diagnostic("code", help, slice, unit.source.buffer);
  // }

  // resolver::Resolver resolver(&context.root_scope);
  // resolver.resolve_ast(unit);

  // RuntimeScope scope;
  // Executor executor(&scope);

  // for (auto &node : unit.ast.get_nodes()) { executor.execute_node(unit, node); }

  // optimazer::optimize_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);
  // debug::ast::print_ast(unit.ast);

  // resolver::Resolver resolver(builtin_scope.get_scope());

  // resolver.resolve_ast(unit.ast);

  return 0;
}
