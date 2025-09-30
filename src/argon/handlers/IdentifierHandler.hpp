#pragma once
#include "argon/argon_descriptor.hpp"
#include "core/base/handler_base.hpp"

class IdentifierHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &charStream, const DescriptorContext &context, size_t lineNumber) override {

    if (!charStream.hasNext() || !std::isalpha(charStream.current())) {
      return std::nullopt;
    }

    size_t start = charStream.position();
    charStream.saveState();

    std::string lexeme;

    while (charStream.hasNext() && (std::isalnum(charStream.current()) || charStream.current() == '_')) {
      lexeme += charStream.advance();
    }

    if (lexeme.empty()) {
      charStream.rollback();
      return std::nullopt;
    }

    auto descriptor = context.getById((DescriptorID::IDENTIFIER));
    if (!descriptor || descriptor.value()->type != DescriptorType::IDENTIFIER) {
      charStream.rollback();
      return std::nullopt;
    }
    return Token(descriptor.value(), lexeme, SourceLocation{lineNumber, start, charStream.position()});
  }
};
