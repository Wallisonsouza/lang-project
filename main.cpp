/* #include "TypeHandler.hpp"
#include "core/Lexer.hpp"
#include "registry/TokenRegistry.hpp"
#include <iostream>
#include <string>

int main() {

  OperatorRegistry::addOperator("+", "Plus");
  OperatorRegistry::addOperator("-", "Minus");
  OperatorRegistry::addOperator("*", "Multiply");
  OperatorRegistry::addOperator("/", "Divide");
  OperatorRegistry::addOperator("=", "Assign");
  OperatorRegistry::addOperator("==", "Equal");
  OperatorRegistry::addOperator("!=", "NotEqual");
  OperatorRegistry::addOperator("<", "Less");
  OperatorRegistry::addOperator(">", "Greater");
  OperatorRegistry::addOperator("<=", "LessEqual");
  OperatorRegistry::addOperator(">=", "GreaterEqual");
  OperatorRegistry::addOperator("&&", "And");
  OperatorRegistry::addOperator("||", "Or");
  OperatorRegistry::addOperator("!", "Not");

  KeywordRegistry::addKeyword("const", "Const");
  KeywordRegistry::addKeyword("if", "If");
  KeywordRegistry::addKeyword("else", "Else");
  KeywordRegistry::addKeyword("return", "Return");
  KeywordRegistry::addKeyword("while", "While");
  KeywordRegistry::addKeyword("for", "For");
  KeywordRegistry::addKeyword("break", "Break");
  KeywordRegistry::addKeyword("continue", "Continue");

  PrimitiveRegistry::addPrimitive("int", "Int");
  PrimitiveRegistry::addPrimitive("float", "Float");
  PrimitiveRegistry::addPrimitive("bool", "Bool");
  PrimitiveRegistry::addPrimitive("char", "Char");
  PrimitiveRegistry::addPrimitive("string", "String");
  PrimitiveRegistry::addPrimitive("void", "Void");

  PunctuationRegistry::addPunctuation(";", "Semicolon");
  PunctuationRegistry::addPunctuation(":", "Colon");
  PunctuationRegistry::addPunctuation(",", "Comma");
  PunctuationRegistry::addPunctuation(".", "Dot");
  PunctuationRegistry::addPunctuation("(", "OpenParen");
  PunctuationRegistry::addPunctuation(")", "CloseParen");
  PunctuationRegistry::addPunctuation("{", "OpenBrace");
  PunctuationRegistry::addPunctuation("}", "CloseBrace");
  PunctuationRegistry::addPunctuation("[", "OpenBracket");
  PunctuationRegistry::addPunctuation("]", "CloseBracket");

  // Código de exemplo
  std::string code = "const test: int = 109278 const pi = 3.14;";
  Lexer lexer(code);
  lexer.addHandler(5, std::make_unique<OperatorHandler>());
  /*   lexer.addHandler(1, std::make_unique<KeywordHandler>());
    lexer.addHandler(2, std::make_unique<IdentifierHandler>());
    lexer.addHandler(3, std::make_unique<FloatHandler>());
    lexer.addHandler(4, std::make_unique<IntHandler>());

   lexer.addHandler(0, std::make_unique<TypeHandler>()); lexer.addHandler(5,
  std::make_unique<OperatorHandler>()); lexer.addHandler(6,
  std::make_unique<PunctuationHandler>());

// Tokenizar
std::vector<Token> tokens = lexer.tokenize();

// Printar tokens
for (const auto &t : tokens) {
  std::cout << "Token {\n";
  std::cout << "  lexeme: \"" << t.lexeme << "\",\n";
  if (t.descriptor) {
    std::cout << "  category: \"" << t.descriptor->category << "\",\n";
  }
  std::cout << "  start: " << t.start << ",\n";
  std::cout << "  end: " << t.end << "\n";
  std::cout << "}\n";
}

return 0;
}
*/

#include "argon/plugins/call_ast.hpp"
#include "core/Lexer.hpp"
#include "core/Parser.hpp"
#include "core/context/descriptor_context.hpp"
#include "core/context/handler_context.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "argon/argon_main.hpp"

std::vector<std::string> readFileLines(const std::string &path, bool removeWhiteSpace = false) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("Não foi possível abrir o arquivo: " + path);
  }

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(file, line)) {
    if (removeWhiteSpace) {
      line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char c) { return !std::isspace(c); }));
      line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char c) { return !std::isspace(c); }).base(), line.end());
    }

    if (!line.empty()) {
      lines.push_back(line);
    }
  }

  return lines;
}

int main() {

  try {
    std::unique_ptr<DescriptorContext> descriptorContext = createArgonDesciptorContext();
    std::unique_ptr<HandlerContext> handlerContext = createArgonHandlerContext();

    std::vector<std::string> argonScrypt = readFileLines("../test.txt", true);
    Stream<std::string> lineStream(argonScrypt);

    std::vector<Token> tokens = Lexer::tokenize(lineStream, *descriptorContext, *handlerContext);
    Stream<Token> tokenStream(tokens);

    Parser parser;
    parser.addPlugin(1, std::make_unique<CallPlugin>());

    auto ast = parser.parse(tokenStream);

    Environment env;

    std::shared_ptr<Environment> console = createStandardConsoleLibrarie();
    env.importAll(*console);

    for (auto &ast : ast) {
      ast->execute(env);
    }

  } catch (const std::exception &e) {
    std::cerr << "Erro: " << e.what() << std::endl;
  }

  return 0;
}

/*  Parser parser;
    parser.addPlugin(1, std::make_unique<CallPlugin>());

    auto ast = parser.parse(tokenStream);

    Environment env;

    std::shared_ptr<Environment> console = consoleLib();
    env.importAll(*console);

    for (auto &ast : ast) {
      ast->execute(env);
      std::cout << ast->toString();
    } */