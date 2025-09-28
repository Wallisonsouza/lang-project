#include "Lexer.hpp"
#include <algorithm>
#include <cctype>

Lexer::Lexer(const std::string &source)
    : stream(std::vector<char>(source.begin(), source.end())) {}

void Lexer::addHandler(int priority, std::unique_ptr<HandlerBase> handler) {
  handlers.push_back({priority, std::move(handler)});

  // ordena assim que adiciona
  std::sort(handlers.begin(), handlers.end(),
            [](const HandlerEntry &a, const HandlerEntry &b) {
              return a.priority < b.priority;
            });
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;

  while (stream.hasNext()) {
    skipWhitespace();

    bool matched = false;

    for (auto &entry : handlers) {
      auto result = entry.handler->match(stream);
      if (result.has_value()) {
        tokens.push_back(result.value());
        matched = true;
        break;
      }
    }

    if (!matched) {
      stream.advance();
    }
  }
  return tokens;
}

void Lexer::skipWhitespace() {
  while (stream.hasNext() && std::isspace(stream.current())) {
    stream.advance();
  }
}
