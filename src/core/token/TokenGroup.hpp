#pragma once
#include <cstdint>

namespace lang::core {
enum class TokenGroup : uint8_t { Keyword, Operator, Punctuation, Literal, Identifier, Type, Error };
}