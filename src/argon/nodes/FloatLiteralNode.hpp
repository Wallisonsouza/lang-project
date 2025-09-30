#pragma once
#include "core/ast.hpp"

struct FloatLiteralNode : public ASTNode {
  float value;
  explicit FloatLiteralNode(float v) : value(v) {}
  LanguagePrimitives execute(Environment &) override { return value; }

  std::string toString() const override { return std::to_string(value); }
};
