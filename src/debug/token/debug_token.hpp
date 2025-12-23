#pragma once
#include "core/token/Token.hpp"
#include "debug/console/console.hpp"
#include "debug_token_group.hpp"
#include "debug_token_kind.hpp"
#include "engine/CompilationUnit.hpp"
#include <string>

namespace debug::token {

#define C_RESET "\033[0m"
#define C_BLUE "\033[34m"
#define C_GREEN "\033[32m"
#define C_YELLOW "\033[33m"

inline void print_token(const CompilationUnit &unit,
                        const core::token::Token *token) {

  if (!token)
    return;

  std::string kind = "[UnknownKind]";
  std::string group = "[UnknownGroup]";

  if (token->descriptor) {

    kind = token_kind_to_str(token->descriptor->kind);

    group = token_group_to_str(token->descriptor->group);
  }

  const std::string text = utils::Utf::utf32to8(token->span.view());

  std::ostringstream oss;
  oss << C_BLUE << "Token" << C_RESET << " {\n"
      << "  " << C_GREEN << "Kind" << C_RESET << ": " << kind << "\n"
      << "  " << C_GREEN << "Group" << C_RESET << ": " << group << "\n"
      << "  " << C_YELLOW << "Text" << C_RESET << ": \"" << text << "\"\n"
      << "  Line: " << token->range.begin.line
      << " | Start: " << token->range.begin.column
      << " | End: " << token->range.end.column << "\n}";

  Console::debug(oss.str());
}
} // namespace debug::token