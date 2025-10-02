/* #pragma once
#include "HandlerBase.hpp"
#include "TokenDescriptor.hpp"
#include <cctype>
#include <optional>
#include <string>

class KeywordHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &stream,
                             const Context &context) override {

    if (!stream.hasNext() || !std::isalpha(stream.current())) {
      return std::nullopt;
    }

    size_t start = stream.position();
    stream.saveState();

    std::string lexeme = stream.readWhileString(
        [](char c) { return std::isalnum(c) || c == '_'; });

    auto descriptor = context.getByLexeme(lexeme);
    if (!descriptor || descriptor.value()->type != DescriptorType::KEYWORD) {
      stream.rollback();
      return std::nullopt;
    }

    return Token(descriptor.value(), lexeme, start, stream.position());
  }
};
 */