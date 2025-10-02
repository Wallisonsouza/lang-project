#pragma once
#include "core/ast.hpp"

struct BoolLiteralNode : public Node {
  bool value;

  explicit BoolLiteralNode(bool v) : value(v) {}

  LanguagePrimitives execute(Environment &) override { return value; }

  std::string toString() const override { return value ? "true" : "false"; }
};
