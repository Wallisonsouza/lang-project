#pragma once
#include "context/descriptor_context.hpp"
#include "context/handler_context.hpp"
#include "core/Stream.hpp"
#include "core/Token.hpp"
#include <vector>

class Lexer {
public:
  static std::vector<Token> tokenize(Stream<std::string> &lineStream, const DescriptorContext &descriptors, const HandlerContext &handlers) {
    std::vector<Token> tokens;

    while (lineStream.hasNext()) {
      const std::string &line = lineStream.current();
      Stream<char> charStream(std::vector<char>(line.begin(), line.end()));

      while (charStream.hasNext()) {
        bool matched = false;

        for (const auto &entry : handlers.getHandlers()) {
          auto result = entry.handler->match(charStream, descriptors, lineStream.position());
          if (result.has_value()) {
            tokens.push_back(result.value());
            matched = true;
            break;
          }
        }

        if (!matched) {
          charStream.advance();
        }
      }

      lineStream.advance();
    }

    return tokens;
  }
};
