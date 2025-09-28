#pragma once
#include "core/Stream.hpp"
#include "core/Token.hpp"
#include <optional>

class HandlerBase {
public:
  virtual ~HandlerBase() = default;
  virtual std::optional<Token> match(Stream<char> &stream) = 0;
};
