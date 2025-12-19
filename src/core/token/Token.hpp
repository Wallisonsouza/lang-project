#pragma once

#include "core/text/TextSpan.hpp"
#include "core/token/Location.hpp"
#include "core/token/TokenDescriptor.hpp"

namespace core::token {

struct Token {
  const TokenDescriptor *descriptor = nullptr;
  source::Span span{};
  SourceRange range{};

  constexpr Token() = default;

  constexpr Token(const TokenDescriptor *desc, source::Span sp, SourceRange rg) : descriptor(desc), span(sp), range(rg) {}
};

} // namespace core::token
