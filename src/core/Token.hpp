#pragma once
#include "TokenDescriptor.hpp"
#include <memory>
#include <sstream>
#include <string>

struct Token {
  std::shared_ptr<TokenDescriptor> descriptor;
  std::string lexeme;
  size_t start;
  size_t end;

  Token(std::shared_ptr<TokenDescriptor> descriptor, const std::string &lexeme,
        size_t start, size_t end)
      : descriptor(descriptor), lexeme(lexeme), start(start), end(end) {}

  std::string toString() const {
    std::ostringstream oss;
    oss << "Token {\n";
    oss << "  lexeme: \"" << lexeme << "\",\n";
    if (descriptor) {
      oss << "  id: \"" << descriptor->id << "\",\n";
      oss << "  type: \"" << descriptor->type << "\"\n";
    }
    oss << "  start: " << start << ",\n";
    oss << "  end: " << end << "\n";
    oss << "}";
    return oss.str();
  }
};
