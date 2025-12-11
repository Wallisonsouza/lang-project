#pragma once

#include "core/diagnostic/Diagnostic.hpp"
#include "core/table/AliasTable.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"
#include "core/text/TextBuffer.hpp"
#include "core/token/Token.hpp"
#include <memory>
#include <vector>

namespace interpreter::core {

struct LangData {
  TextBuffer buffer;
  DiagnosticEngine diagnostics;
  TokenTable token_table;
  AliasTable alias_table;
  PrecedenceTable precedence_table;

  std::vector<Token> tokens_storage;

  explicit LangData(TextBuffer buf) : buffer(std::move(buf)) {}

  Token *make_token(TokenDescriptor *desc, TextSpan span) {
    tokens_storage.emplace_back(desc, span);
    return &tokens_storage.back();
  }
};

inline std::shared_ptr<LangData> makeLangData(TextBuffer buffer) { return std::make_shared<LangData>(std::move(buffer)); }

} // namespace interpreter::core
