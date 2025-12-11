#include "argon/argon_main.hpp"
#include "core/LangData.hpp"
#include "core/debug/TokenDebug.hpp"
#include "core/lexer/Lexer.hpp"

#include "core/lexer/plugins/identifier_plugin.hpp"
#include "core/lexer/plugins/number_plugin.hpp"
#include "core/lexer/plugins/operator_plugin.hpp"
#include "core/lexer/plugins/string_plugin.hpp"
#include "core/parser/Parser.hpp"
#include "core/parser/VariableDeclarationPlugin.hpp"
#include "core/parser/expression/IdentifierExpressionPlugin.hpp"
#include "core/parser/expression/NumberExpressionPlugin.hpp"
#include "core/parser/expression/StringExpressionPlugin.hpp"
#include "core/text/TextBuffer.hpp"
#include "core/utils/Utf8.hpp"

#include <chrono>
#include <iostream>
#include <memory>
#include <string>

int main() {

  auto buffer = TextBuffer("../examples/test.orb");
  std::size_t text_size_bytes = buffer.u32_size();
  std::cout << "Text size: " << text_size_bytes << " bytes\n";

  auto data = interpreter::core::makeLangData(buffer);

  argon::bind(*data);

  interpreter::core::DiagnosticEngine diag;

  interpreter::lexer::Lexer lexer(*data);

  lexer.add_plugin(std::make_shared<interpreter::lexer::plugins::StringPlugin>(), 0);
  lexer.add_plugin(std::make_shared<interpreter::lexer::plugins::NumberPlugin>(), 2);
  lexer.add_plugin(std::make_shared<interpreter::lexer::plugins::IdentifierPlugin>(), 1);
  lexer.add_plugin(std::make_shared<interpreter::lexer::plugins::OperatorPlugin>());

  // --- Benchmark tokenization ---
  auto start_lex = std::chrono::high_resolution_clock::now();
  lexer.generate_tokens();
  auto end_lex = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> lex_time = end_lex - start_lex;
  std::cout << "Tokenization time: " << lex_time.count() << " ms\n";
  std::cout << "Tokens generated: " << data->tokens_storage.size() << "\n";

  // for (auto &token : data->tokens_storage) { interpreter::debug::TokenDebug::print_token(*data, token); }

  // interpreter::parser::Parser parser(*data);
  // parser.statement_plugins.push_back(std::make_shared<interpreter::parser::plugins::VariableDeclarationPlugin>());
  // parser.expression_plugins.push_back(std::make_shared<IdentifierExpressionPlugin>());
  // parser.expression_plugins.push_back(std::make_shared<NumberExpressionPlugin>());
  // parser.expression_plugins.push_back(std::make_shared<StringExpressionPlugin>());

  // // --- Benchmark parsing ---
  // auto start_parse = std::chrono::high_resolution_clock::now();
  // auto ast = parser.generate_ast(tokens);
  // auto end_parse = std::chrono::high_resolution_clock::now();
  // std::chrono::duration<double, std::milli> parse_time = end_parse - start_parse;
  // std::cout << "Parsing time: " << parse_time.count() << " ms\n";
  // std::cout << "AST nodes generated: " << ast.size() << "\n";

  // --- Print diagnostics ---
  // for (auto &d : diag.get_all()) {
  //   std::cout << d.file << ":" << d.line << ":" << d.column << " [" << (d.severity == interpreter::core::Diagnostic::Severity::Error ? "Error" : "Warning") << "/"
  //             << (d.category == interpreter::core::Diagnostic::Category::Lexer ? "Lexer" : "Parser") << "] " << d.message << "\n";
  // }

  return 0;
}
