#pragma once
#include "argon/argon_descriptor.hpp"
#include "core/base/StructuralNode.hpp"
#include "core/base/StructuralPlugin.hpp"
#include "memory"

struct FunctionCallStructuralNode : public StructuralNode {
  Token identifier;
  std::vector<Token> argTokens;

  FunctionCallStructuralNode(Token funcToken, std::vector<Token> args) : identifier(std::move(funcToken)), argTokens(std::move(args)) {}

  std::string toString() override {
    std::string result = identifier.lexeme + "(";
    for (size_t i = 0; i < argTokens.size(); ++i) {
      result += argTokens[i].lexeme;
      if (i + 1 < argTokens.size())
        result += ", ";
    }
    result += ")";
    return result;
  }
};

class FunctionCallStructuralPlugin : public StructuralPlugin {
public:
  std::unique_ptr<StructuralNode> match(Stream<Token> &stream) override {
    if (!stream.hasNext())
      return nullptr;

    Token funcName = stream.current();
    if (funcName.descriptor->type != DescriptorType::IDENTIFIER)
      return nullptr;

    stream.advance();

    if (!stream.hasNext() || stream.current().descriptor->id != DescriptorID::OPEN_PAREN)
      return nullptr; // espera '('

    stream.advance(); // consome '('

    std::vector<Token> args;

    while (stream.hasNext() && stream.current().descriptor->id != DescriptorID::CLOSE_PAREN) {
      args.push_back(stream.current());
      stream.advance();

      if (stream.hasNext() && stream.current().descriptor->id == DescriptorID::COMMA) {
        stream.advance(); // consome ','
      }
    }

    if (!stream.hasNext() || stream.current().descriptor->id != DescriptorID::CLOSE_PAREN)
      return nullptr; // parêntese não fechado

    stream.advance(); // consome ')'

    return std::make_unique<FunctionCallStructuralNode>(funcName, std::move(args));
  }
};
