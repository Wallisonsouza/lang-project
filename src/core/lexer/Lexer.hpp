#pragma once
#include "core/LangData.hpp"
#include "core/token/Token.hpp"
#include "core/utils/LazyText.hpp"
#include "core/utils/Stream.hpp"
#include <memory>

class Lexer {
public:
  std::vector<std::shared_ptr<lang::core::Token>> generate_tokens(lang::utils::LazyText &text, lang::core::LangData &data) {

    std::vector<std::shared_ptr<lang::core::Token>> tokens;

    while (!text.isEOF()) {
      std::u32string line = text.getLine();
      std::vector<char32_t> chars(line.begin(), line.end());
      lang::core::Stream<char32_t> stream(chars);

      while (!stream.eof()) {
        bool matched = false;

        auto token = data.matchers.run(stream, data);

        if (token) {
          tokens.push_back(token);
          matched = true;
        }

        if (!matched)
          stream.advance();
      }

      text.advance();
    }

    return tokens;
  }
};
