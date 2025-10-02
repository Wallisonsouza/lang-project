#pragma once

#include "argon/argon_descriptor.hpp"
#include "core/Token.hpp"
#include "core/base/HandlerPluginBase.hpp"

class PunctuationHandler : public HandlerPlugin {
public:
  std::optional<Token> match(Stream<char> &charStream, const DescriptorContext &context, size_t lineNumber) override {

    if (!charStream.hasNext()) {
      return std::nullopt;
    }

    char c = charStream.current();
    std::string lexeme(1, c);

    auto descriptor = context.getByLexeme(lexeme);

    if (!descriptor || descriptor.value()->type != DescriptorType::PUNCTUATION) {
      return std::nullopt;
    }

    size_t start = charStream.position();
    charStream.advance();

    return Token(descriptor.value(), lexeme, SourceLocation{lineNumber, start, charStream.position()});
  }
};
