#pragma once
#include <cstdint>

namespace interpreter::core {
enum class TokenGroup : uint8_t { Keyword, Operator, Punctuation, Literal, Type, Error, Name };
}