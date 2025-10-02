/* #pragma once
#include "HandlerBase.hpp"
#include <cctype>
#include <string>
#include <unordered_set>

class TypeHandler : public HandlerBase {
public:
  static void addType(const std::string &type) { types.insert(type); }

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

    if (types.find(lexeme) != types.end()) {
      return Token{TokenType::Type, lexeme, start, stream.position()};
    }

    stream.restore();
    return std::nullopt;
  }

private:
  static inline std::unordered_set<std::string> types = {
      "int", "float", "bool", "string", "char", "void"};
};
 */