#pragma once

#include "core/token/Token.hpp"
#include "core/token/TokenGroup.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "debug/console/console.hpp"
#include <sstream>
#include <string>

namespace debug::engine {

constexpr const char *token_group_to_str(core::token::TokenGroup grp) {
  using G = core::token::TokenGroup;
  switch (grp) {
  case G::Name: return "Name";
  case G::Keyword: return "Keyword";
  case G::Operator: return "Operator";
  case G::Punctuation: return "Punctuation";
  case G::Error: return "Error";
  case G::Literal: return "Literal";
  }
  return "<UnknownGroup>";
}

constexpr const char *token_kind_to_str(core::token::TokenKind kin) {
  using K = core::token::TokenKind;
  switch (kin) {
  case K::UseKeyword: return "UseKeyword";
  case K::Dot: return "Dot";
  case K::Function: return "Function";
  case K::IfKeyword: return "If";
  case K::Else: return "Else";
  case K::While: return "While";
  case K::For: return "For";
  case K::Return: return "Return";
  case K::Equals: return "Equals";
  case K::Assign: return "Assign";
  case K::Ternary: return "Ternary";
  case K::Plus: return "Plus";
  case K::Minus: return "Minus";
  case K::Star: return "Star";
  case K::Slash: return "Slash";
  case K::Colon: return "Colon";
  case K::Comma: return "Comma";
  case K::Semicolon: return "Semicolon";
  case K::OpenParen: return "LParen";
  case K::CloseParen: return "RParen";
  case K::OpenBrace: return "LBrace";
  case K::CloseBrace: return "RBrace";
  case K::Identifier: return "Identifier";
  case K::NumberLiteral: return "NumberLiteral";
  case K::StringLiteral: return "StringLiteral";
  case K::Space: return "Space";
  case K::EndOfFile: return "EndOfFile";
  }
  return "<UnknownKind>";
}

inline std::string sanitize_text(std::string text, size_t max = 40) {
  for (char &c : text) {
    if (c == '\n')
      c = '~'; // ou '^'
    else if (c == '\t')
      c = '>';
  }

  if (text.size() > max) text = text.substr(0, max) + "...";

  return text;
}

// ================= DUMP TOKEN =================

inline void dump_token(const core::token::Token &token) {

  const char *kind = "<no-descriptor>";
  const char *group = "<no-descriptor>";

  if (token.descriptor) {
    kind = token_kind_to_str(token.descriptor->kind);
    group = token_group_to_str(token.descriptor->group);
  }

  std::string text{token.slice.span.view()};

  std::ostringstream oss;
  oss << "Token" << " {\n"
      << "  " << "kind " << ": " << kind << "\n"
      << "  " << "group" << ": " << group << "\n"
      << "  " << "text " << ": \"" << text << "\"\n"
      << "  range : " << token.slice.range.begin.line << ":" << token.slice.range.begin.column << " → " << token.slice.range.end.line << ":" << token.slice.range.end.column << "\n"
      << "  offset: " << token.slice.range.begin.offset << " → " << token.slice.range.end.offset << "\n"
      << "}";

  Console::debug(oss.str());
}

inline void dump_tokens(core::token::TokenStream &tokens) {

  for (auto &token : tokens.get_tokens()) { dump_token(*token); }
}
} // namespace debug::engine
