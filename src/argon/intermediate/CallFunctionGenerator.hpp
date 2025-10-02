/* #pragma once
#include "core/Parser.hpp"
#include "core/Token.hpp"
#include "core/ast.hpp"

#include "argon/argon_descriptor.hpp"
#include "argon/nodes/CallNode.hpp"

#include <memory>
#include <string>
#include <vector>

namespace PreAST {
class CallFunctionPreNode {
public:
  std::string &name;
  std::vector<std::unique_ptr<Token>> rawArgs;
};

class PreProcessor {
  virtual ~PreProcessor() = default;
  virtual std::unique_ptr<Node> match(Stream<Token> &tokens) = 0;
}

class CallFunctionGenerator : public PreProcessor {
public:
  std::unique_ptr<Node> match(Stream<Token> &stream) override {
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
    stream.advance();

    while (stream.hasNext() && stream.current().descriptor->id != DescriptorID::CLOSE_PAREN) {
      Token argToken = stream.current();

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
};

} // namespace PreAST */