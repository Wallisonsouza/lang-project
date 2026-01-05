// #include "engine/CompilationUnit.hpp"
// #include "engine/lexer/lexer.hpp"
// #include "engine/parser/parser.hpp"
// #include "engine/resolver/Resolver.hpp"

// struct CompilationUnitWrapper {
//   CompilationUnit unit;
//   Lexer lexer;
//   Parser parser;
//   resolver::Resolver resolver;

//   CompilationUnitWrapper(GlobalContext &global_ctx, const std::string &file_path)
//       : unit(global_ctx.language_context, core::source::Source(file_path)), lexer(unit), parser(unit, unit.tokens), resolver(&global_ctx.language_context.root_scope) {
//     resolver.diag_target = &unit.diagnostics;
//     ayla::modules::create_module_console(unit);
//   }

//   void compile() {
//     lexer.generate_tokens();

//     while (!unit.tokens.is_end()) {
//       auto node = parser.parse_statement();
//       if (node)
//         unit.ast.add_root(node);
//       else
//         unit.tokens.advance();
//     }

//     resolver.resolve_ast(unit);
//   }

//   void run(GlobalContext &global_ctx) {
//     for (auto &node : unit.ast.get_nodes()) { global_ctx.executor.execute_node(unit, node); }
//   }
// };
