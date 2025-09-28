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

#include "CallPlugin.hpp"
#include "Environment.hpp"
#include "IdentifierHandler.hpp"
#include "KeywordHandler.hpp"
#include "Parser.hpp"
#include "PunctuationHandler.hpp"
#include "Stream.hpp"
#include "Token.hpp"
#include "TokenDescriptor.hpp"
#include "TypeHandler.hpp"
#include "core/Lexer.hpp"
#include "handlers/NumberHandler.hpp"
#include "handlers/OperatorHandler.hpp"
#include "node/Nodes.hpp"
#include <iostream>
#include <memory>

std::shared_ptr<Environment> createStdLib() {
  auto env = std::make_shared<Environment>();

  auto printFunc = std::make_shared<NativeFunctionNode>(
      [](const std::vector<LanguagePrimitives> &args) -> LanguagePrimitives {
        for (const auto &arg : args) {
          std::visit([](auto &&val) { std::cout << val << " "; }, arg);
        }
        std::cout << std::endl;
        return 0;
      });

  env->exportSymbol("print", printFunc);
  return env;
}

int main() {

  std::shared_ptr<Environment> standardLib = createStdLib();

  LangDescriptor::addDescriptor(DescriptorID::PLUS, "+",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::MINUS, "-",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::MULTIPLY, "*",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::DIVIDE, "/",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::ASSIGN, "=",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::EQUAL,
                                "==", DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::NOT_EQUAL,
                                "!=", DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::LESS, "<",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::GREATER, ">",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::LESS_EQUAL,
                                "<=", DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::GREATER_EQUAL,
                                ">=", DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::AND, "&&",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::OR, "||",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::NOT, "!",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::POWER, "^",
                                DescriptorType::OPERATOR);
  LangDescriptor::addDescriptor(DescriptorID::MODULO, "%",
                                DescriptorType::OPERATOR);

  LangDescriptor::addDescriptor(DescriptorID::IF, "if",
                                DescriptorType::KEYWORD);
  LangDescriptor::addDescriptor(DescriptorID::ELSE, "else",
                                DescriptorType::KEYWORD);
  LangDescriptor::addDescriptor(DescriptorID::WHILE, "while",
                                DescriptorType::KEYWORD);
  LangDescriptor::addDescriptor(DescriptorID::FOR, "for",
                                DescriptorType::KEYWORD);
  LangDescriptor::addDescriptor(DescriptorID::BREAK, "break",
                                DescriptorType::KEYWORD);
  LangDescriptor::addDescriptor(DescriptorID::CONTINUE, "continue",
                                DescriptorType::KEYWORD);
  LangDescriptor::addDescriptor(DescriptorID::RETURN, "return",
                                DescriptorType::KEYWORD);
  LangDescriptor::addDescriptor(DescriptorID::CONST, "const",
                                DescriptorType::KEYWORD);

  LangDescriptor::addDescriptor(DescriptorID::INT, "int", DescriptorType::TYPE);
  LangDescriptor::addDescriptor(DescriptorID::FLOAT, "float",
                                DescriptorType::TYPE);
  LangDescriptor::addDescriptor(DescriptorID::BOOL, "bool",
                                DescriptorType::TYPE);
  LangDescriptor::addDescriptor(DescriptorID::CHAR, "char",
                                DescriptorType::TYPE);
  LangDescriptor::addDescriptor(DescriptorID::STRING, "string",
                                DescriptorType::TYPE);
  LangDescriptor::addDescriptor(DescriptorID::VOID, "void",
                                DescriptorType::TYPE);

  LangDescriptor::addDescriptor(DescriptorID::SEMICOLON, ";",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::COLON, ":",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::COMMA, ",",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::DOT, ".",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::OPEN_PAREN, "(",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::CLOSE_PAREN, ")",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::OPEN_BRACE, "{",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::CLOSE_BRACE, "}",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::OPEN_BRACKET, "[",
                                DescriptorType::PUNCTUATION);
  LangDescriptor::addDescriptor(DescriptorID::CLOSE_BRACKET, "]",
                                DescriptorType::PUNCTUATION);

  LangDescriptor::addDescriptor(DescriptorID::INT_LITERAL, "",
                                DescriptorType::LITERAL);
  LangDescriptor::addDescriptor(DescriptorID::FLOAT_LITERAL, "",
                                DescriptorType::LITERAL);
  LangDescriptor::addDescriptor(DescriptorID::STRING_LITERAL, "",
                                DescriptorType::LITERAL);
  LangDescriptor::addDescriptor(DescriptorID::CHAR_LITERAL, "",
                                DescriptorType::LITERAL);
  LangDescriptor::addDescriptor(DescriptorID::BOOL_LITERAL, "",
                                DescriptorType::LITERAL);
  LangDescriptor::addDescriptor(DescriptorID::IDENTIFIER, "",
                                DescriptorType::IDENTIFIER);

  Lexer lexer(" print(11.12);");

  lexer.addHandler(1, std::make_unique<KeywordHandler>());
  lexer.addHandler(2, std::make_unique<IdentifierHandler>());
  lexer.addHandler(3, std::make_unique<NumberHandler>());
  lexer.addHandler(5, std::make_unique<OperatorHandler>());
  lexer.addHandler(6, std::make_unique<PunctuationHandler>());

  std::vector<Token> tokens = lexer.tokenize();

  Parser parser;
  parser.addPlugin(1, std::make_unique<CallPlugin>());

  Stream<Token> tokensStream(tokens);
  auto ast = parser.parse(tokensStream);

  Environment env;
  env.importAll(*standardLib);

  for (auto &ast : ast) {
    ast->execute(env);
  }

  /*   Parser parser;
    Stream<Token> stream(tokens);

    parser.addPlugin(1, std::make_unique<CallPlugin>());
    auto ast = parser.parse(stream);

    std::shared_ptr<Environment> std = createGlobalEnv();

    for (const std::unique_ptr<ASTNode> &node : ast) {
      node->execute(*std);
    } */

  return 0;
}
