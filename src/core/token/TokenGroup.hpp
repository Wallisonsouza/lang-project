#pragma once
#include <cstdint>

enum class TokenGroup : uint8_t { Keyword, Operator, Punctuation, Literal, Identifier, Type, Error };