#pragma once
#include "HandlerBase.hpp"
#include "TokenDescriptor.hpp"
#include <cctype>
#include <optional>
#include <string>

class KeywordHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &stream) override {

    if (!stream.hasNext() || !std::isalpha(stream.current())) {
      return std::nullopt;
    }

    size_t start = stream.position();
    stream.save();

    std::string lexeme = stream.readWhileString(
        [](char c) { return std::isalnum(c) || c == '_'; });

    auto descriptor = LangDescriptor::getByLexeme(lexeme);
    if (!descriptor || descriptor.value()->type != DescriptorType::KEYWORD) {
      stream.restore();
      return std::nullopt;
    }

    return Token(descriptor.value(), lexeme, start, stream.position());
  }
};
