#pragma once

#include "core/source/TextStream.hpp"
#include "core/token/Token.hpp"
#include "engine/CompilationUnit.hpp"
#include "utils/Unicode.hpp"

struct Lexer {
private:
  CompilationUnit &unit;
  core::source::TextStream stream;

  core::token::Token *match_token() {

    if (auto t = match_string()) return t;

    if (auto t = match_number()) return t;

    if (auto t = match_identifier()) return t;

    if (auto t = match_operator()) return t;

    return nullptr;
  }

public:
  Lexer(CompilationUnit &unit) : unit(unit), stream(unit.source.buffer) {};

  core::token::Token *match_identifier();
  core::token::Token *match_string();
  core::token::Token *match_number();
  core::token::Token *match_operator();

  void skip_whitespace_and_comments(core::source::TextStream &stream) {
    while (!stream.eof()) {
      char32_t c = stream.peek();

      // Espaços em branco
      if (utils::Unicode::is_white_space(c)) {
        stream.advance();
        continue;
      }

      // Comentário de linha //
      if (c == U'/' && stream.peek_n(1) == U'/') {
        stream.advance_n(2);
        while (stream.peek() != U'\n' && !stream.eof()) stream.advance();
        continue;
      }

      // Comentário de bloco /* ... */
      if (c == U'/' && stream.peek_n(1) == U'*') {
        stream.advance_n(2);
        while (!stream.eof()) {
          if (stream.peek() == U'*' && stream.peek_n(1) == U'/') {
            stream.advance_n(2);
            break;
          }
          stream.advance();
        }
        continue;
      }

      break;
    }
  }

  void generate_tokens() {

    while (!stream.eof()) {
      skip_whitespace_and_comments(stream);

      auto start_state = stream.get_state();
      auto *token = match_token();

      if (!token) {
        auto slice = Slice{.range = start_state.range_to(stream.get_state()), .span = start_state.span_to(stream.get_state())};
        // unit.diagnostics.emit({DiagnosticCode::UnexpectedToken, slice}, unit);
        stream.advance();
      }
    }
  }
};
