#pragma once
#include "core/Stream.hpp"
#include "core/Token.hpp"
#include "core/base/StructuralNode.hpp"
#include <memory>

struct StructuralPlugin {
  virtual ~StructuralPlugin() = default;
  virtual std::unique_ptr<StructuralNode> match(Stream<Token> &tokens) = 0;
};
