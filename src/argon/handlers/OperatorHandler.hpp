/* #include "HandlerBase.hpp"
#include "TokenDescriptor.hpp"
#include <string>

class OperatorHandler : public HandlerBase {
public:
  std::optional<Token> match(Stream<char> &stream,
                             const Context &context) override {
    if (!stream.hasNext())
      return std::nullopt;

    size_t start = stream.position();
    stream.saveState();

    std::string lexeme;
    lexeme += stream.advance();

    if (stream.hasNext()) {
      std::string twoChar = lexeme + stream.current();
      if (context.getByLexeme(twoChar)) {
        lexeme += stream.advance();
      }
    }

    auto descriptor = context.getByLexeme(lexeme);

    if (descriptor && descriptor.value()->type == DescriptorType::OPERATOR) {
      return Token{descriptor.value(), lexeme, start, stream.position()};
    }

    stream.rollback();
    return std::nullopt;
  }
};
 */