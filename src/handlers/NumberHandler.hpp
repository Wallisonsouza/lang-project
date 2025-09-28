#pragma once
#include "Token.hpp"
#include "TokenDescriptor.hpp"
#include "handlers/HandlerBase.hpp"
#include <algorithm>
#include <cctype>
#include <optional>
#include <string>

class NumberHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &stream) override {
    if (!stream.hasNext()) {
      return std::nullopt;
    }

    size_t start = stream.position();
    stream.save();

    std::optional<DescriptorPtr> plusTokenOpt =
        LangDescriptor::getById(DescriptorID::PLUS);
    std::optional<DescriptorPtr> minusTokenOpt =
        LangDescriptor::getById(DescriptorID::MINUS);
    std::optional<DescriptorPtr> dotTokenOpt =
        LangDescriptor::getById(DescriptorID::DOT);

    if (!plusTokenOpt || !minusTokenOpt || !dotTokenOpt) {
      return std::nullopt;
    }

    std::string lexeme;

    if (stream.current() == plusTokenOpt.value()->lexeme[0] ||
        stream.current() == minusTokenOpt.value()->lexeme[0]) {
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
      stream.restore();
      return std::nullopt;
    }

    std::optional<DescriptorPtr> descriptor =
        hasDot ? LangDescriptor::getById(DescriptorID::FLOAT_LITERAL)
               : LangDescriptor::getById(DescriptorID::INT_LITERAL);

    if (!descriptor || descriptor.value()->type != DescriptorType::LITERAL) {
      stream.restore();
      return std::nullopt;
    }

    return Token(descriptor.value(), lexeme, start, stream.position());
  }
};
