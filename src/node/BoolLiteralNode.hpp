#pragma once
#include "Ast.hpp"

struct BoolLiteralNode : public ASTNode {
  bool value;

  explicit BoolLiteralNode(bool v) : value(v) {}

  LanguagePrimitives execute(Environment &) override { return value; }

  std::string toString() const override { return value ? "true" : "false"; }
};
