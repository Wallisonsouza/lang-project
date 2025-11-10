#pragma once

#include "core/LangData.hpp"
#include "core/plugin/Plugin.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "core/utils/TextStream.hpp"
#include "core/utils/Unicode.hpp"
#include <memory>

using namespace lang::core;
using namespace lang::utils;

namespace argon::plugins {

class KeywordAndIdentifierHandler : public Plugin {
private:
  static bool isIdentifierStart(char32_t ch) noexcept { return Unicode::isAlpha(ch) || ch == U'_'; }

  static bool isIdentifierChar(char32_t ch) noexcept { return Unicode::isAlpha(ch) || Unicode::isDigit(ch) || ch == U'_'; }

public:
  std::shared_ptr<Token> exec(LangData &data, TextStream &stream) override {

    const char32_t *startPtr = stream.current();

    if (!startPtr) {
      return nullptr;
    }

    if (!isIdentifierStart(*startPtr)) {
      return nullptr;
    }

    const size_t startPos = stream.position();
    stream.advance();

    while (stream.has_next()) {
      const char32_t *ch = stream.current();
      if (!ch || !isIdentifierChar(*ch))
        break;
      stream.advance();
    }

    const size_t endPos = stream.position();
    std::u32string word = stream.slice(startPos, endPos);

    const TokenDescriptor *desc = data.descriptors.get_descriptor(word);

    auto location = lang::core::Location{data.line, startPos, stream.position()};

    if (!desc) {
      const TokenDescriptor descriptor = {TokenKind::Identifier, TokenGroup::Identifier, word, {}};

      return std::make_shared<lang::core::Token>(&descriptor, word, location);
    }

    return std::make_shared<lang::core::Token>(desc, word, location);
  }
};

} // namespace argon::plugins
