#pragma once
#include <cstdint>

namespace core::token {
enum class TokenGroup : uint8_t { Keyword, Operator, Punctuation, Literal, Whitespace, Error, Name };
}