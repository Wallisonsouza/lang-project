#pragma once

#include "core/table/AliasTable.hpp"
#include "core/table/PrecedenceTable.hpp"
#include "core/table/TokenTable.hpp"
#include "core/text/TextBuffer.hpp"
#include "core/token/Token.hpp"
#include "diagnostic/DiagnosticEngine.hpp"
#include <vector>

namespace core {

struct LangData {
  text::TextBuffer buffer;
  
  diagnostics::DiagnosticEngine diagnostics;

  table::TokenTable token_table;
  table::AliasTable alias_table;
  table::PrecedenceTable precedence_table;

  std::vector<token::Token> tokens_storage;

  explicit LangData(text::TextBuffer buf) : buffer(std::move(buf)) {}
};

} // namespace core
