#pragma once
#include <string>

class DescriptorType {
public:
  inline static const std::string OPERATOR = "OPERATOR";
  inline static const std::string KEYWORD = "KEYWORD";
  inline static const std::string TYPE = "TYPE";
  inline static const std::string PUNCTUATION = "PUNCTUATION";
  inline static const std::string IDENTIFIER = "IDENTIFIER";
  inline static const std::string LITERAL = "LITERAL";
};

class DescriptorID {
public:
  inline static const std::string IDENTIFIER = "IDENTIFIER";
  inline static const std::string PLUS = "PLUS";
  inline static const std::string MINUS = "MINUS";
  inline static const std::string MULTIPLY = "MULTIPLY";
  inline static const std::string DIVIDE = "DIVIDE";
  inline static const std::string ASSIGN = "ASSIGN";
  inline static const std::string EQUAL = "EQUAL";
  inline static const std::string NOT_EQUAL = "NOT_EQUAL";
  inline static const std::string LESS = "LESS";
  inline static const std::string GREATER = "GREATER";
  inline static const std::string LESS_EQUAL = "LESS_EQUAL";
  inline static const std::string GREATER_EQUAL = "GREATER_EQUAL";
  inline static const std::string AND = "AND";
  inline static const std::string OR = "OR";
  inline static const std::string NOT = "NOT";
  inline static const std::string POWER = "POWER";
  inline static const std::string MODULO = "MODULO";

  // Palavras-chave
  inline static const std::string IF = "IF";
  inline static const std::string ELSE = "ELSE";
  inline static const std::string WHILE = "WHILE";
  inline static const std::string FOR = "FOR";
  inline static const std::string BREAK = "BREAK";
  inline static const std::string CONTINUE = "CONTINUE";
  inline static const std::string RETURN = "RETURN";
  inline static const std::string CONST = "CONST";

  // Tipos
  inline static const std::string INT = "INT";
  inline static const std::string FLOAT = "FLOAT";
  inline static const std::string BOOL = "BOOL";
  inline static const std::string CHAR = "CHAR";
  inline static const std::string STRING = "STRING";
  inline static const std::string VOID = "VOID";

  // Literais
  inline static const std::string INT_LITERAL = "INT_LITERAL";
  inline static const std::string FLOAT_LITERAL = "FLOAT_LITERAL";
  inline static const std::string STRING_LITERAL = "STRING_LITERAL";
  inline static const std::string CHAR_LITERAL = "CHAR_LITERAL";
  inline static const std::string BOOL_LITERAL = "BOOL_LITERAL";

  // Pontuação
  inline static const std::string SEMICOLON = "SEMICOLON";
  inline static const std::string COLON = "COLON";
  inline static const std::string COMMA = "COMMA";
  inline static const std::string DOT = "DOT";
  inline static const std::string OPEN_PAREN = "OPEN_PAREN";
  inline static const std::string CLOSE_PAREN = "CLOSE_PAREN";
  inline static const std::string OPEN_BRACE = "OPEN_BRACE";
  inline static const std::string CLOSE_BRACE = "CLOSE_BRACE";
  inline static const std::string OPEN_BRACKET = "OPEN_BRACKET";
  inline static const std::string CLOSE_BRACKET = "CLOSE_BRACKET";
};
