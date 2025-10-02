#pragma once
#include "core/Stream.hpp"
#include "core/Token.hpp"
#include "core/ast.hpp"
#include <memory>

struct ParserPluginBase {
  virtual ~ParserPluginBase() = default;
  virtual std::unique_ptr<Node> match(Stream<Token> &tokens) = 0;
};
