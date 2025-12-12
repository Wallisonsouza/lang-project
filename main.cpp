#include "argon/argon_main.hpp"
#include "core/LangData.hpp"
#include "core/text/TextBuffer.hpp"
#include "debug/Console.hpp"
#include "debug/TokenDebug.hpp"
#include "lexer/Lexer.hpp"
#include "lexer/plugins/identifier_plugin.hpp"
#include "lexer/plugins/number_plugin.hpp"
#include "lexer/plugins/operator_plugin.hpp"
#include "lexer/plugins/string_plugin.hpp"
#include "utils/TextLoader.hpp"

#include <memory>
#include <string>

int main() {

  auto text = utils::TextLoader::load_file("../examples/test.orb");

  auto buffer = core::text::TextBuffer(text);

  auto data = core::LangData(buffer);
  argon::bind(data);

  lexer::Lexer lexer(data);
  lexer.add_plugin(std::make_shared<lexer::plugins::StringPlugin>(), 1);
  lexer.add_plugin(std::make_shared<lexer::plugins::NumberPlugin>(), 2);
  lexer.add_plugin(std::make_shared<lexer::plugins::IdentifierPlugin>(), 3);
  lexer.add_plugin(std::make_shared<lexer::plugins::OperatorPlugin>(), 0);

  debug::Console::time("lexer");

  lexer.generate_tokens();

  debug::Console::timeEnd("lexer");
  debug::Console::log("Tokens generated: ", data.tokens_storage.size());

  for (auto &token : data.tokens_storage) {
    debug::TokenDebug::print_token(data, token);
  }

  return 0;
}

// int main() {

//   auto buffer = TextBuffer("../examples/test.orb");
//   std::size_t text_size_bytes = buffer.u32_size();
//   std::cout << "Text size: " << text_size_bytes << " bytes\n";

//   auto data = interpreter::core::makeLangData(buffer);

//   argon::bind(*data);

//   interpreter::core::DiagnosticEngine diag;

//   interpreter::lexer::Lexer lexer(*data);

//   lexer.add_plugin(
//       std::make_shared<interpreter::lexer::plugins::StringPlugin>(), 1);
//   lexer.add_plugin(
//       std::make_shared<interpreter::lexer::plugins::NumberPlugin>(), 2);
//   lexer.add_plugin(
//       std::make_shared<interpreter::lexer::plugins::IdentifierPlugin>(), 3);
//   lexer.add_plugin(
//       std::make_shared<interpreter::lexer::plugins::OperatorPlugin>(), 0);

//   // --- Benchmark tokenization ---
//   auto start_lex = std::chrono::high_resolution_clock::now();
//   lexer.generate_tokens();
//   auto end_lex = std::chrono::high_resolution_clock::now();
//   std::chrono::duration<double, std::milli> lex_time = end_lex - start_lex;
//   std::cout << "Tokenization time: " << lex_time.count() << " ms\n";
//   std::cout << "Tokens generated: " << data->tokens_storage.size() << "\n";

//   for (auto &token : data->tokens_storage) {
//     interpreter::debug::TokenDebug::print_token(*data, token);
//   }

//   // interpreter::parser::Parser parser(*data);
//   //
//   parser.statement_plugins.push_back(std::make_shared<interpreter::parser::plugins::VariableDeclarationPlugin>());
//   //
//   parser.expression_plugins.push_back(std::make_shared<IdentifierExpressionPlugin>());
//   //
//   parser.expression_plugins.push_back(std::make_shared<NumberExpressionPlugin>());
//   //
//   parser.expression_plugins.push_back(std::make_shared<StringExpressionPlugin>());

//   // // --- Benchmark parsing ---
//   // auto start_parse = std::chrono::high_resolution_clock::now();
//   // auto ast = parser.generate_ast(tokens);
//   // auto end_parse = std::chrono::high_resolution_clock::now();
//   // std::chrono::duration<double, std::milli> parse_time = end_parse -
//   // start_parse; std::cout << "Parsing time: " << parse_time.count() << "
//   // ms\n"; std::cout << "AST nodes generated: " << ast.size() << "\n";

//   // --- Print diagnostics ---
//   // for (auto &d : diag.get_all()) {
//   //   std::cout << d.file << ":" << d.line << ":" << d.column << " [" <<
//   //   (d.severity == interpreter::core::Diagnostic::Severity::Error ?
//   "Error" :
//   //   "Warning") << "/"
//   //             << (d.category ==
//   //             interpreter::core::Diagnostic::Category::Lexer ? "Lexer" :
//   //             "Parser") << "] " << d.message << "\n";
//   // }

//   return 0;
// }
