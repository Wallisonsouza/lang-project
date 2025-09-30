#pragma once
#include "TokenDescriptor.hpp"
#include <sstream>
#include <string>

struct SourceLocation {
  size_t line;
  size_t start;
  size_t end;
};

struct Token {
  DescriptorPtr descriptor;
  std::string lexeme;
  SourceLocation location;

  Token(DescriptorPtr desc, std::string lex, const SourceLocation &loc) : descriptor(desc), lexeme(std::move(lex)), location(loc) {}

  std::string toString() const {
    std::ostringstream oss;
    oss << "Token {\n";
    oss << "  lexeme: \"" << lexeme << "\",\n";
    if (descriptor) {
      oss << "  id: \"" << descriptor->id << "\",\n";
      oss << "  type: \"" << descriptor->type << "\",\n";
    }
    oss << "  line: " << location.line << ",\n";
    oss << "  start: " << location.start << ",\n";
    oss << "  end: " << location.end << ",\n";
    oss << "}";
    return oss.str();
  }
};
