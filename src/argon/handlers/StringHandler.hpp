#pragma once

#include "argon/argon_descriptor.hpp"
#include "core/Token.hpp"
#include "core/base/HandlerPluginBase.hpp"

class StringHandler : public HandlerPlugin {
public:
  std::optional<Token> match(Stream<char> &stream, const DescriptorContext &context, size_t lineNumber) override {
    if (!stream.hasNext() || (stream.current() != '"' && stream.current() != '\'')) {
      return std::nullopt;
    }

    char quote = stream.current();
    size_t start = stream.position();
    stream.advance(); // pular a aspa inicial

    std::string lexeme;
    bool closed = false;

    while (stream.hasNext()) {
      char c = stream.current();

      if (c == '\\') {
        stream.advance(); // consumir '\'
        if (!stream.hasNext())
          break;

        char next = stream.current();
        switch (next) {
        case 'n':
          lexeme.push_back('\n');
          break;
        case 't':
          lexeme.push_back('\t');
          break;
        case '\\':
          lexeme.push_back('\\');
          break;
        case '"':
          lexeme.push_back('"');
          break;
        case '\'':
          lexeme.push_back('\'');
          break;
        default:
          lexeme.push_back(next);
          break;
        }

        stream.advance(); // consumir caractere escapado
        continue;         // evita dar advance() de novo no final
      } else if (c == quote) {
        closed = true;
        stream.advance(); // consumir a aspa de fechamento
        break;
      } else {
        lexeme.push_back(c);
        stream.advance(); // só aqui no caso normal
      }
    }

    if (!closed) {
      std::ostringstream oss;
      oss << "Erro léxico: string não fechada. Início: " << start << ", valor: \"" << stream.position() << "\"";
      throw std::runtime_error(oss.str());
    }

    auto descriptor = context.getById(DescriptorID::STRING_LITERAL);

    return Token(descriptor.value(), lexeme, SourceLocation{lineNumber, start, stream.position()});
  }
};
