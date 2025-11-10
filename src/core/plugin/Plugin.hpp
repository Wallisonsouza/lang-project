#pragma once
#include "core/token/Token.hpp"
#include "core/utils/Stream.hpp"
#include "core/utils/TextStream.hpp"
#include <memory>

namespace lang::core {
class LangData;
class Plugin {
public:
  virtual ~Plugin()                                                                                = default;
  virtual std::shared_ptr<lang::core::Token> exec(LangData &data, lang::utils::TextStream &stream) = 0;
};

} // namespace lang::core
