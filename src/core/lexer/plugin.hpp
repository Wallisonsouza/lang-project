#pragma once

#include "core/plugin/Plugin.hpp"
#include "core/text/TextStream.hpp"

namespace interpreter::core {
struct LangData;
}

namespace interpreter::lexer {

class LexerPlugin : public interpreter::core::Plugin {
public:
  virtual bool match(TextStream &stream, interpreter::core::LangData &data) = 0;
};

} // namespace interpreter::lexer
