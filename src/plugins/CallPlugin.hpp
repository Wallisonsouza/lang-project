#pragma once
#include "Ast.hpp"
#include "Parser.hpp"
#include "node/CallNode.hpp"
#include "node/FloatLiteralNode.hpp"
#include "node/IntLiteralNode.hpp"
#include "node/StringLiteralNode.hpp"
#include <memory>
#include <vector>

class CallPlugin : public ParserPluginBase {
public:
  std::unique_ptr<ASTNode> match(Stream<Token> &tokens, size_t &pos) override {
    if (!tokens.hasNext())
      return nullptr;
    size_t startPos = pos;

    Token token = tokens.current();
    if (token.descriptor->type != DescriptorType::IDENTIFIER)
      return nullptr;

    std::string funcName = token.lexeme;

    tokens.advance();
    pos++;

    if (!tokens.hasNext() ||
        tokens.current().descriptor->id != DescriptorID::OPEN_PAREN) {
      pos = startPos;

      return nullptr;
    }

    tokens.advance();
    pos++;

    std::vector<std::unique_ptr<ASTNode>> args;

    while (tokens.hasNext() &&
           tokens.current().descriptor->id != DescriptorID::CLOSE_PAREN) {
      token = tokens.current();
      if (token.descriptor->id == DescriptorID::INT_LITERAL) {
        args.push_back(
            std::make_unique<IntLiteralNode>(std::stoi(token.lexeme)));
      } else if (token.descriptor->id == DescriptorID::FLOAT_LITERAL) {
        args.push_back(
            std::make_unique<FloatLiteralNode>(std::stod(token.lexeme)));
      } else if (token.descriptor->id == DescriptorID::STRING_LITERAL) {
        args.push_back(std::make_unique<StringLiteralNode>(token.lexeme));
      } else {
        pos = startPos;
        return nullptr;
      }
      tokens.advance();
      pos++;

      if (tokens.hasNext() &&
          tokens.current().descriptor->id == DescriptorID::COMMA) {
        tokens.advance();
        pos++;
      }
    }

    if (!tokens.hasNext() ||
        tokens.current().descriptor->id != DescriptorID::CLOSE_PAREN) {
      pos = startPos;
      return nullptr;
    }

    tokens.advance();
    pos++;

    return std::make_unique<CallNode>(funcName, std::move(args));
  }
};