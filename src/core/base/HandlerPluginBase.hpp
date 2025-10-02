#pragma once
#include "core/Stream.hpp"
#include "core/Token.hpp"
#include "core/context/descriptor_context.hpp"
#include <optional>

class HandlerPlugin {
public:
  virtual ~HandlerPlugin() = default;
  virtual std::optional<Token> match(Stream<char> &chars, const DescriptorContext &context, size_t lineNumber) = 0;
};
