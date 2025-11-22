#pragma once

#include "core/LangData.hpp"
#include "core/helper/TokenMatchHelper.hpp"
#include "core/token/Token.hpp"
#include "core/utils/Stream.hpp"
#include <memory>

namespace argon::matchers {
class OperatorMatcher : public lang::core::Matcher {
  std::shared_ptr<lang::core::Token> match(lang::core::Stream<char32_t> &stream, lang::core::LangData &data) override {
    size_t start = stream.get_current_position();
    std::u32string temp;

    TokenDescriptor *last_desc = nullptr;
    size_t last_valid_pos = start;

    while (!stream.eof()) {
      temp.push_back(stream.current());

      if (auto *desc = lang::helper::TokenMatchHelper::resolve_descriptor(data, temp)) {
        last_desc = desc;
        last_valid_pos = stream.get_current_position() + 1;
      }

      if (!lang::helper::TokenMatchHelper::has_prefix(data, temp)) { break; }

      stream.consume();
    }

    if (last_desc) {
      stream.reset(start);
      stream.advance(last_valid_pos - start);

      std::u32string lex = temp.substr(0, last_valid_pos - start);
      return std::make_shared<lang::core::Token>(last_desc, lex, lang::core::Location{0, start, last_valid_pos});
    }

    stream.reset(start);
    return nullptr;
  }
};
} // namespace argon::matchers