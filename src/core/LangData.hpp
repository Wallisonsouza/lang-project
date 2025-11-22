#pragma once

#include "core/manager/MatcherManager.hpp"
#include "core/table/AliasTable.hpp"
#include "core/table/TokenTable.hpp"

namespace lang::core {

struct LangData {

  TokenTable token_table;
  AliasTable alias_table;

  lang::core::MatcherManager matchers;
};

inline LangData makeLangData() { return LangData{}; }

} // namespace lang::core
