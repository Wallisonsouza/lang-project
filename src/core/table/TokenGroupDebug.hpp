#pragma once

#include "core/token/TokenGroup.hpp"
#include <unordered_map>

namespace lang::debug {

class TokenGroupDebug {
public:
  inline static const std::unordered_map<lang::core::TokenGroup, const char *> group_map = {
      {lang::core::TokenGroup::Keyword, "Keyword"}, {lang::core::TokenGroup::Operator, "Operator"},     {lang::core::TokenGroup::Punctuation, "Punctuation"},
      {lang::core::TokenGroup::Literal, "Literal"}, {lang::core::TokenGroup::Identifier, "Identifier"}, {lang::core::TokenGroup::Type, "Type"},
      {lang::core::TokenGroup::Error, "Error"},
  };
};

} // namespace lang::debug
