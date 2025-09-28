#pragma once
#include "HandlerBase.hpp"
#include "TokenDescriptor.hpp"
#include <cctype>

class IdentifierHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &stream) override {

    if (!stream.hasNext() || !std::isalpha(stream.current())) {
      return std::nullopt;
    }

    size_t start = stream.position();
    stream.save();

    std::string lexeme;

    while (stream.hasNext() &&
           (std::isalnum(stream.current()) || stream.current() == '_')) {
      lexeme += stream.advance();
    }

    if (lexeme.empty()) {
      stream.restore();
      return std::nullopt;
    }

    std::optional<DescriptorPtr> descriptor =
        LangDescriptor::getById((DescriptorID::IDENTIFIER));
    if (!descriptor || descriptor.value()->type != DescriptorType::IDENTIFIER) {
      stream.restore();
      return std::nullopt;
    }
    return Token(descriptor.value(), lexeme, start, stream.position());
  }
};
