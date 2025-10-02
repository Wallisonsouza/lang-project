/* #pragma once
#include "Ast.hpp"
#include "Parser.hpp"
#include "Stream.hpp"
#include "Token.hpp"
#include "TokenDescriptor.hpp"

#include "nodes/AssignmentNode.hpp"
#include "nodes/BoolLiteralNode.hpp"
#include "nodes/FloatLiteralNode.hpp"
#include "nodes/IntLiteralNode.hpp"
#include "nodes/StringLiteralNode.hpp"

class AssignmentPlugin : public ParserPluginBase {
public:
  std::unique_ptr<ASTNode> match(Stream<Token> &stream) override {

    if (!stream.hasNext()) {
      return nullptr;
    }

    size_t startPos = stream.position();

    Token token = stream.current();
    if (token.descriptor->id != DescriptorID::CONST) {
      return nullptr;
    }

    stream.advance();

    if (!stream.hasNext()) {
      return nullptr;
    }
    token = stream.current();
    if (token.descriptor->id != DescriptorID::IDENTIFIER) {
      return nullptr;
    }
    std::string varName = token.lexeme;
    stream.advance();

    if (!stream.hasNext()) {
      return nullptr;
    }
    token = stream.current();
    if (token.descriptor->id != DescriptorID::ASSIGN) {
      return nullptr;
    }
    stream.advance();

    if (!stream.hasNext()) {
      return nullptr;
    }
    token = stream.current();

    std::unique_ptr<ASTNode> valueNode;

    if (token.descriptor->id == DescriptorID::INT_LITERAL) {
      valueNode = std::make_unique<IntLiteralNode>(std::stoi(token.lexeme));

    } else if (token.descriptor->id == DescriptorID::FLOAT_LITERAL) {
      valueNode = std::make_unique<FloatLiteralNode>(std::stod(token.lexeme));

    } else if (token.descriptor->id == DescriptorID::STRING_LITERAL) {
      valueNode = std::make_unique<StringLiteralNode>(token.lexeme);

    } else if (token.descriptor->id == DescriptorID::BOOL_LITERAL) {
      valueNode = std::make_unique<BoolLiteralNode>(token.lexeme == "true");

    } else {
      return nullptr;
    }

    stream.advance();

    if (stream.hasNext() &&
        stream.current().descriptor->id == DescriptorID::SEMICOLON) {
      stream.advance();
    }

    return std::make_unique<AssignmentNode>(varName, std::move(valueNode));
  }
};
 */