/*

struct AssignmentNode : public ASTNode {
  std::string name;
  std::unique_ptr<ASTNode> value;
  Value execute(Environment &) override {}
  AssignmentNode(std::string n, std::unique_ptr<ASTNode> val)
      : name(std::move(n)), value(std::move(val)) {}

  std::string toString() const override {
    return "AssignmentNode { name: \"" + name +
           "\", value: " + value->toString() + " }";
  }
};

#pragma once
#include "Ast.hpp"
#include "Parser.hpp"
#include "Stream.hpp"
#include "Token.hpp"
#include "TokenDescriptor.hpp"
#include "node/Nodes.hpp"

class AssignmentPlugin : public ParserPluginBase {
public:
  std::unique_ptr<ASTNode> match(Stream<Token> &tokens, size_t &pos) override {

    if (!tokens.hasNext())
      return nullptr;
    size_t startPos = pos;

    Token token = tokens.current();
    if (token.descriptor->id != DescriptorID::CONST)
      return nullptr;
    tokens.advance();
    pos++;

    if (!tokens.hasNext()) {
      pos = startPos;
      return nullptr;
    }
    token = tokens.current();
    if (token.descriptor->id != DescriptorID::IDENTIFIER) {
      pos = startPos;
      return nullptr;
    }
    std::string varName = token.lexeme;
    tokens.advance();
    pos++;

    if (!tokens.hasNext()) {
      pos = startPos;
      return nullptr;
    }
    token = tokens.current();
    if (token.descriptor->id != DescriptorID::ASSIGN) {
      pos = startPos;
      return nullptr;
    }
    tokens.advance();
    pos++;

    if (!tokens.hasNext()) {
      pos = startPos;
      return nullptr;
    }
    token = tokens.current();

    std::unique_ptr<ASTNode> valueNode;

    if (token.descriptor->id == DescriptorID::INT_LITERAL) {
      valueNode = std::make_unique<IntLiteralNode>(std::stoi(token.lexeme));
    } else if (token.descriptor->id == DescriptorID::FLOAT_LITERAL) {
      valueNode = std::make_unique<FloatLiteralNode>(std::stod(token.lexeme));
    } else if (token.descriptor->id == DescriptorID::STRING_LITERAL) {
      valueNode = std::make_unique<StringLiteralNode>(token.lexeme);
    } else if (token.descriptor->id == DescriptorID::CHAR_LITERAL) {
      valueNode = std::make_unique<CharLiteralNode>(token.lexeme[0]);
}
else if (token.descriptor->id == DescriptorID::BOOL_LITERAL) {
     valueNode = std::make_unique<BoolLiteralNode>(token.lexeme ==
   * "true");
}
else {
  pos = startPos;
  return nullptr;
}

tokens.advance();
pos++;

// Opcional: ponto e vírgula
if (tokens.hasNext() &&
    tokens.current().descriptor->id == DescriptorID::SEMICOLON) {
  tokens.advance();
  pos++;
}

return std::make_unique<AssignmentNode>(varName, std::move(valueNode));
}
}
;
*/