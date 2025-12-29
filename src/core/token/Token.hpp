#pragma once

#include "core/token/Location.hpp"
#include "core/token/TokenDescriptor.hpp"

namespace core::token {

struct Token {
  const TokenDescriptor *descriptor = nullptr;
  Slice slice;

  constexpr Token() = default;

  constexpr Token(const TokenDescriptor *desc, Slice slice)
      : descriptor(desc), slice(slice) {}
};

} // namespace core::token
