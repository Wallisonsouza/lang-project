#pragma once

#include "core/text/TextSpan.hpp"
#include "core/token/TokenDescriptor.hpp"

namespace interpreter::core {

struct Token {
  const TokenDescriptor *descriptor;
  TextSpan span;

  constexpr Token(const TokenDescriptor *desc, TextSpan sp) : descriptor(desc), span(sp) {}
};

} // namespace interpreter::core
