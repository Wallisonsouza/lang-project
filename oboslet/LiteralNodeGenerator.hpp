/* #pragma once
#include "argon/argon_descriptor.hpp"
#include "argon/nodes/FloatLiteralNode.hpp"
#include "argon/nodes/IntLiteralNode.hpp"
#include "argon/nodes/StringLiteralNode.hpp"
#include "core/Parser.hpp"

class LiteralNodeGenerator : public ParserPluginBase {
public:
  std::unique_ptr<Node> match(Stream<Token> &stream) override {
    if (!stream.hasNext()) {
      return nullptr;
    }

    Token token = stream.current();

    std::unique_ptr<Node> node = nullptr;

    if (token.descriptor->id == DescriptorID::INT_LITERAL) {
      node = std::make_unique<IntLiteralNode>(std::stoi(token.lexeme));

    } else if (token.descriptor->id == DescriptorID::FLOAT_LITERAL) {
      node = std::make_unique<FloatLiteralNode>(std::stof(token.lexeme));

    } else if (token.descriptor->id == DescriptorID::STRING_LITERAL) {
      node = std::make_unique<StringLiteralNode>(token.lexeme);
    }

    if (!node) {
      return nullptr;
    }

    stream.advance();
    return node;
  }
}; */