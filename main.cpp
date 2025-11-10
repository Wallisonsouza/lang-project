#include "argon/argon_main.hpp"
#include "core/LangData.hpp"
#include "core/token/TokenDebug.hpp"
#include "core/utils/LazyText.hpp"
#include "core/utils/Stream.hpp"
#include "core/utils/TextStream.hpp"
#include "core/utils/Utf8.hpp"
#include <cstdint>
#include <iostream>
#include <string>

class Tokenizer {
  lang::utils::LazyText &text;
  lang::core::LangData &data;

public:
  Tokenizer(lang::utils::LazyText &text, lang::core::LangData &data) : text(text), data(data) {}

  std::vector<std::shared_ptr<lang::core::Token>> tokenizeAll() {

    std::vector<std::shared_ptr<lang::core::Token>> tokens;

    while (!text.isEOF()) {
      lang::utils::TextStream stream(text.getLine());
      data.line = text.getLineIndex();

      while (stream.has_next()) {
        bool matched = false;

        for (auto &entry : data.handlers.get_all()) {
          if (stream.has_next() && entry) {

            auto token = entry->exec(data, stream);

            if (token) {
              matched = true;
              tokens.push_back(token);
              break;
            }
          }
        }

        if (!matched) {
          stream.advance();
        }
      }

      text.advance();
    }

    return tokens;
  }
};

int main() {

  //----config-------------------
  auto data = lang::core::makeLangData();
  argon::create_tokens_context(data);
  argon::create_tokens_handler(data);

  //----load-------------------
  lang::utils::LazyText text("../examples/test.orb");

  //---tokenizer---------
  Tokenizer tokenizer(text, data);
  auto tokens = tokenizer.tokenizeAll();

  for (auto &token : tokens) {
    lang::debug::debug_token(token);
  }

  return 0;
}
