/* #pragma once
#include "Ast.hpp"
#include "Parser.hpp"
#include "TokenDescriptor.hpp"
#include "nodes/CallNode.hpp"
#include "nodes/FloatLiteralNode.hpp"
#include "nodes/IntLiteralNode.hpp"
#include "nodes/StringLiteralNode.hpp"
#include <memory>
#include <vector>

class CallPlugin : public ParserPluginBase {
public:
  std::unique_ptr<ASTNode> match(Stream<Token> &stream) override {
    if (!stream.hasNext())
      return nullptr;

    size_t startPosition = stream.position();
    Token token = stream.current();

    if (token.descriptor->type != DescriptorType::IDENTIFIER) {
      return nullptr;
    }

    stream.saveState();

    std::string funcName = token.lexeme;
    stream.advance();

    if (!stream.hasNext() || stream.current().descriptor->id != DescriptorID::OPEN_PAREN) {
      stream.rollback();
      return nullptr;
    }
    stream.advance(); // consome '('

    std::vector<std::unique_ptr<ASTNode>> args;

    while (stream.hasNext() && stream.current().descriptor->id != DescriptorID::CLOSE_PAREN) {
      Token argToken = stream.current();

      if (argToken.descriptor->id == DescriptorID::INT_LITERAL) {
        args.push_back(std::make_unique<IntLiteralNode>(std::stoi(argToken.lexeme)));
      } else if (argToken.descriptor->id == DescriptorID::FLOAT_LITERAL) {
        args.push_back(std::make_unique<FloatLiteralNode>(std::stod(argToken.lexeme)));
      } else if (argToken.descriptor->id == DescriptorID::STRING_LITERAL) {
        args.push_back(std::make_unique<StringLiteralNode>(argToken.lexeme));
      } else {
        stream.rollback();
        return nullptr;
      }

      stream.advance();

      if (stream.hasNext() && stream.current().descriptor->id == DescriptorID::COMMA) {
        stream.advance();
      }
    }

    // fecha parêntese
    if (!stream.hasNext() || stream.current().descriptor->id != DescriptorID::CLOSE_PAREN) {
      stream.rollback();
      return nullptr;
    }

    stream.advance(); // consome ')'

    return std::make_unique<CallNode>(funcName, std::move(args));
  }
}; */