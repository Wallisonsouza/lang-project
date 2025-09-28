#pragma once
#include "Ast.hpp"

struct IntLiteralNode : public ASTNode {
  int value;
  explicit IntLiteralNode(int v) : value(v) {}
  LanguagePrimitives execute(Environment &) override { return value; }

  std::string toString() const override { return std::to_string(value); }
};
