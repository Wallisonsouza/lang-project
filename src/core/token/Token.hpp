#pragma once

#include "core/text/TextSpan.hpp"
#include "core/token/TokenDescriptor.hpp"

namespace core::token {

struct Token {
  const TokenDescriptor *descriptor;
  text::TextSpan span;

  constexpr Token(const TokenDescriptor *desc, text::TextSpan sp)
      : descriptor(desc), span(sp) {}
};

} // namespace core::token
