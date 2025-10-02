#pragma once
#include "argon/argon_descriptor.hpp"
#include "core/base/HandlerPluginBase.hpp"
#include "core/context/descriptor_context.hpp"
#include <algorithm>

class NumberHandler : public HandlerPlugin {
public:
  std::optional<Token> match(Stream<char> &stream, const DescriptorContext &context, size_t lineNumber) override {
    if (!stream.hasNext()) {
      return std::nullopt;
    }

    size_t start = stream.position();
    stream.saveState();

    std::optional<DescriptorPtr> plusTokenOpt = context.getById(DescriptorID::PLUS);
    std::optional<DescriptorPtr> minusTokenOpt = context.getById(DescriptorID::MINUS);
    std::optional<DescriptorPtr> dotTokenOpt = context.getById(DescriptorID::DOT);

    if (!plusTokenOpt || !minusTokenOpt || !dotTokenOpt) {
      return std::nullopt;
    }

    std::string lexeme;

    if (stream.current() == plusTokenOpt.value()->lexeme[0] || stream.current() == minusTokenOpt.value()->lexeme[0]) {
      lexeme += stream.advance();
    }

    bool hasDot = false;

    std::string numberPart = stream.readWhileString([&](char c) {
      if (std::isdigit(c))
        return true;
      if (c == dotTokenOpt.value()->lexeme[0] && !hasDot) {
        hasDot = true;
        return true;
      }
      return false;
    });

    lexeme += numberPart;

    bool hasDigit = std::any_of(lexeme.begin(), lexeme.end(), ::isdigit);
    if (!hasDigit) {
      stream.rollback();
      return std::nullopt;
    }

    std::optional<DescriptorPtr> descriptor = hasDot ? context.getById(DescriptorID::FLOAT_LITERAL) : context.getById(DescriptorID::INT_LITERAL);

    if (!descriptor || descriptor.value()->type != DescriptorType::LITERAL) {
      stream.rollback();
      return std::nullopt;
    }

    return Token(descriptor.value(), lexeme, SourceLocation{lineNumber, start, stream.position()});
  }
};
