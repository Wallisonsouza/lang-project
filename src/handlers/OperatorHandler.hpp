#include "HandlerBase.hpp"
#include "TokenDescriptor.hpp"
#include <string>

class OperatorHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &stream) override {
    if (!stream.hasNext())
      return std::nullopt;

    size_t start = stream.position();
    stream.save();

    std::string lexeme;
    lexeme += stream.advance();

    if (stream.hasNext()) {
      std::string twoChar = lexeme + stream.current();
      if (LangDescriptor::getByLexeme(twoChar)) {
        lexeme += stream.advance();
      }
    }

    auto descriptor = LangDescriptor::getByLexeme(lexeme);

    if (descriptor && descriptor.value()->type == DescriptorType::OPERATOR) {
      return Token{descriptor.value(), lexeme, start, stream.position()};
    }

    stream.restore();
    return std::nullopt;
  }
};
