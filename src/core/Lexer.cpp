/* #include "Lexer.hpp"

Lexer::Lexer(const std::vector<std::string> &source, const DescriptorContext &descriptorCtx, const HandlerContext &handlerCtx) : lineStream(source), descriptors(descriptorCtx), handlers(handlerCtx) {}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;

  while (lineStream.hasNext()) {
    const std::string &line = lineStream.current();
    Stream<char> chars(std::vector<char>(line.begin(), line.end()));

    while (chars.hasNext()) {
      bool matched = false;

      for (const auto &entry : handlers.getHandlers()) {
        auto result = entry.handler->match(chars, descriptors, lineStream.position());
        if (result.has_value()) {
          tokens.push_back(result.value());
          matched = true;
          break;
        }
      }

      if (!matched) {
        chars.advance();
      }
    }

    lineStream.advance();
  }

  return tokens;
}
 */