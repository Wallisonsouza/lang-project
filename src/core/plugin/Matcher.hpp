#include "core/token/Token.hpp"
#include "core/utils/Stream.hpp"
#include <memory>

namespace lang::core {
struct LangData;
}

namespace lang::core {
class Matcher {
public:
  int priority                                                                                                       = 0;
  virtual std::shared_ptr<lang::core::Token> match(lang::core::Stream<char32_t> &stream, lang::core::LangData &data) = 0;
  virtual ~Matcher()                                                                                                 = default;
};

} // namespace lang::core