#include "argon/argon_main.hpp"
#include "core/LangData.hpp"
#include "core/lexer/Lexer.hpp"
#include "core/utils/LazyText.hpp"
#include <string>

#include "core/debug/TokenDebug.hpp"
int main() {

  auto data = lang::core::makeLangData();
  argon::bind(data);

  //---tokenizer---------
  lang::utils::LazyText text("../examples/test.orb");

  auto lexer  = Lexer();
  auto tokens = lexer.generate_tokens(text, data);

  for (auto &token : tokens) {

    lang::debug::TokenDebug::print_token(*token);
  }

  return 0;
}
