#pragma once
#include "HandlerBase.hpp"
#include "TokenDescriptor.hpp"
#include <optional>
#include <string>

class PunctuationHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &stream) override {

    if (!stream.hasNext()) {
      return std::nullopt;
    }

    char c = stream.current();
    std::string lexeme(1, c);

    auto descriptor = LangDescriptor::getByLexeme(lexeme);

    if (!descriptor ||
        descriptor.value()->type != DescriptorType::PUNCTUATION) {
      return std::nullopt;
    }

    size_t start = stream.position();
    stream.advance();

    return Token(descriptor.value(), lexeme, start, stream.position());
  }
};
