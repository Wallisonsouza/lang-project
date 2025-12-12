#pragma once

#include "core/LangData.hpp"
#include "core/plugin/Plugin.hpp"
#include "core/text/TextStream.hpp"
#include "core/token/Token.hpp"
#include <optional>

namespace interpreter::core {
struct LangData;
}

namespace lexer {

class LexerPlugin : public core::Plugin {
public:
  virtual std::optional<core::token::Token>
  match(core::text::TextStream &stream, core::LangData &data) = 0;
};

} // namespace lexer
