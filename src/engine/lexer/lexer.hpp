#pragma once

#include "core/source/SourceBuffer.hpp"
#include "core/source/TextStream.hpp"
#include "core/token/Token.hpp"
#include "core/token/token_stream.hpp"
#include "engine/language_context.hpp"
#include "utils/Unicode.hpp"

struct Lexer {
private:
  core::token::Token *match_token(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out) {

    if (auto t = match_string(stream, context, out)) return t;

    if (auto t = match_number(stream, context, out)) return t;

    if (auto t = match_identifier(stream, context, out)) return t;

    if (auto t = match_operator(stream, context, out)) return t;

    return nullptr;
  }

public:
  core::token::Token *match_identifier(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out);
  core::token::Token *match_string(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out);
  core::token::Token *match_number(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out);
  core::token::Token *match_operator(core::source::TextStream &stream, LanguageContext &context, core::token::TokenStream &out);

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

  void generate_tokens(LanguageContext &context, core::source::SourceBuffer &buff, core::token::TokenStream &out) {

    core::source::TextStream stream(buff);

    while (!stream.eof()) {
      skip_whitespace_and_comments(stream);

      auto start_state = stream.get_state();
      auto *token = match_token(stream, context, out);

      if (!token) {
        auto slice = Slice{.range = start_state.range_to(stream.get_state()), .span = start_state.span_to(stream.get_state())};
        // unit.diagnostics.emit({DiagnosticCode::UnexpectedToken, slice}, unit);
        stream.advance();
      }
    }
  }
};
