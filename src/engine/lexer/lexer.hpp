#pragma once

#include "core/source/TextStream.hpp"
#include "core/token/Token.hpp"
#include "diagnostic/DiagnosticCode.hpp"
#include "engine/CompilationUnit.hpp"
#include "utils/Unicode.hpp"

struct Lexer {
private:
  CompilationUnit &unit;
  core::source::TextStream stream;

public:
  explicit Lexer(CompilationUnit &unit) : unit(unit), stream(unit.source.buffer) {}

  core::token::Token *match_identifier();
  core::token::Token *match_string();
  core::token::Token *match_number();
  core::token::Token *match_operator();

  core::token::Token *match_token() {
    if (auto t = match_string()) return t;
    if (auto t = match_number()) return t;
    if (auto t = match_identifier()) return t;
    if (auto t = match_operator()) return t;
    return nullptr;
  }

  void generate_tokens() {
    while (!stream.eof()) {

      if (utils::Unicode::is_white_space(stream.peek())) {
        stream.advance();
        continue;
      }

      auto start_state = stream.get_state();
      auto *token = match_token();

      if (!token) {
        auto slice = Slice{.range = start_state.range_to(stream.get_state()), .span = start_state.span_to(stream.get_state())};
        unit.diagnostics.emit({DiagnosticCode::UnexpectedToken, slice}, unit);

        stream.advance();
      }
    }
  }
};
