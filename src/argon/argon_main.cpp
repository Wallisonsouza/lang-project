#include "argon/argon_descriptor.hpp"
#include "argon/handlers/IdentifierHandler.hpp"
#include "argon/handlers/NumberHandler.hpp"
#include "argon/handlers/OperatorHandler.hpp"
#include "argon/handlers/PunctuationHandler.hpp"
#include "argon/handlers/StringHandler.hpp"



#include "core/context/descriptor_context.hpp"

#include <memory>

#include "argon_main.hpp"

std::unique_ptr<DescriptorContext> createArgonDesciptorContext() {

  std::unique_ptr<DescriptorContext> context = std::make_unique<DescriptorContext>();
  context->addDescriptor(DescriptorID::PLUS, "+", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::MINUS, "-", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::MULTIPLY, "*", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::DIVIDE, "/", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::ASSIGN, "=", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::EQUAL, "==", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::NOT_EQUAL, "!=", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::LESS, "<", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::GREATER, ">", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::LESS_EQUAL, "<=", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::GREATER_EQUAL, ">=", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::AND, "&&", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::OR, "||", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::NOT, "!", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::POWER, "^", DescriptorType::OPERATOR);
  context->addDescriptor(DescriptorID::MODULO, "%", DescriptorType::OPERATOR);

  context->addDescriptor(DescriptorID::IF, "if", DescriptorType::KEYWORD);
  context->addDescriptor(DescriptorID::ELSE, "else", DescriptorType::KEYWORD);
  context->addDescriptor(DescriptorID::WHILE, "while", DescriptorType::KEYWORD);
  context->addDescriptor(DescriptorID::FOR, "for", DescriptorType::KEYWORD);
  context->addDescriptor(DescriptorID::BREAK, "break", DescriptorType::KEYWORD);
  context->addDescriptor(DescriptorID::CONTINUE, "continue", DescriptorType::KEYWORD);
  context->addDescriptor(DescriptorID::RETURN, "return", DescriptorType::KEYWORD);
  context->addDescriptor(DescriptorID::CONST, "const", DescriptorType::KEYWORD);

  context->addDescriptor(DescriptorID::INT, "int", DescriptorType::TYPE);
  context->addDescriptor(DescriptorID::FLOAT, "float", DescriptorType::TYPE);
  context->addDescriptor(DescriptorID::BOOL, "bool", DescriptorType::TYPE);
  context->addDescriptor(DescriptorID::CHAR, "char", DescriptorType::TYPE);
  context->addDescriptor(DescriptorID::STRING, "string", DescriptorType::TYPE);
  context->addDescriptor(DescriptorID::VOID, "void", DescriptorType::TYPE);

  context->addDescriptor(DescriptorID::SEMICOLON, ";", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::COLON, ":", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::COMMA, ",", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::DOT, ".", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::OPEN_PAREN, "(", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::CLOSE_PAREN, ")", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::OPEN_BRACE, "{", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::CLOSE_BRACE, "}", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::OPEN_BRACKET, "[", DescriptorType::PUNCTUATION);
  context->addDescriptor(DescriptorID::CLOSE_BRACKET, "]", DescriptorType::PUNCTUATION);

  context->addDescriptor(DescriptorID::INT_LITERAL, "", DescriptorType::LITERAL);
  context->addDescriptor(DescriptorID::FLOAT_LITERAL, "", DescriptorType::LITERAL);
  context->addDescriptor(DescriptorID::STRING_LITERAL, "", DescriptorType::LITERAL);
  context->addDescriptor(DescriptorID::CHAR_LITERAL, "", DescriptorType::LITERAL);
  context->addDescriptor(DescriptorID::BOOL_LITERAL, "", DescriptorType::LITERAL);
  context->addDescriptor(DescriptorID::IDENTIFIER, "", DescriptorType::IDENTIFIER);

  return context;
}

std::unique_ptr<Context<HandlerPlugin>> createArgonHandlerContext() {
  std::unique_ptr<Context<HandlerPlugin>> context = std::make_unique<Context<HandlerPlugin>>();
  context->addContext(2, std::make_unique<IdentifierHandler>());
  context->addContext(3, std::make_unique<NumberHandler>());
  context->addContext(5, std::make_unique<OperatorHandler>());
  context->addContext(0, std::make_unique<StringHandler>());
  context->addContext(6, std::make_unique<PunctuationHandler>());

  return context;
  /*

    lexer.addHandler(1, std::make_unique<KeywordHandler>());

    lexer.addHandler(3, std::make_unique<NumberHandler>());
    lexer.addHandler(5, std::make_unique<OperatorHandler>()); */
}
