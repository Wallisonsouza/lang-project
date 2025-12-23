// // ayla/engine/Engine.cpp

// #include "Engine.hpp"
// #include "engine/CompilationUnit.hpp"
// #include "engine/lexer/Lexer.hpp"
// #include "parser/Parser.hpp"

// namespace ayla::engine {

// Engine::Engine(const language::LanguageSpec &lang) : language(lang) {}

// CompilationUnit Engine::compile(core::source::Source &source) {

//   auto *unit = new CompilationUnit(language, source);
//   unit->alias_table.build();

//   lexer::Lexer lexer;
//   lexer.generate_tokens(*unit);

//   parser::Parser parser;
//   parser.generate_ast(*unit);

//   resolver::Resolver resolver(builtin.get_scope());
//   resolver.resolve_ast(unit->ast);

//   return *unit;
// }

// } // namespace ayla::engine
