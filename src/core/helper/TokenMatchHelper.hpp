#pragma once

#include "core/LangData.hpp"
#include "core/token/TokenDescriptor.hpp"

namespace lang::helper {
class TokenMatchHelper {
public:
  static TokenDescriptor *resolve_descriptor(lang::core::LangData &data, const std::u32string &lexeme) {

    if (TokenDescriptor *d = data.token_table.lookup_by_name(lexeme)) { return d; }

    if (TokenDescriptor *a = data.alias_table.lookup_by_name(lexeme)) { return a; }

    return nullptr;
  }

  static bool has_prefix(lang::core::LangData &data, const std::u32string &prefix) {

    if (data.token_table.has_prefix(prefix)) return true;
    if (data.alias_table.has_prefix(prefix)) return true;

    return false;
  }
};

} // namespace lang::helper