#pragma once

#include "core/source/TextStream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/lexer/plugins/match_identifier.hpp"
#include "engine/lexer/plugins/match_number.hpp"
#include "engine/lexer/plugins/match_operator.hpp"
#include "engine/lexer/plugins/match_string.hpp"

namespace lexer {

class Lexer {
public:
  void generate_tokens(CompilationUnit &unit) {
    core::source::TextStream stream(unit.source.buffer);

    while (!stream.eof()) {

      if (utils::Unicode::is_white_space(stream.peek())) {
        stream.advance();
        continue;
      }
      core::token::Token *token = match_token(unit, stream);

      if (!token) {
        stream.advance();
      }
    }
  }

private:
  static core::token::Token *match_token(CompilationUnit &unit,
                                         core::source::TextStream &stream) {
    if (auto t = lexer::match::match_string(unit, stream))
      return t;
    if (auto t = lexer::match::match_number(unit, stream))
      return t;
    if (auto t = lexer::match::match_identifier(unit, stream))
      return t;
    if (auto t = lexer::match::match_operator(unit, stream))
      return t;
    return nullptr;
  }
};

} // namespace lexer
