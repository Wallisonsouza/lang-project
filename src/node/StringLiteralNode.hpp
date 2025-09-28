#pragma once
#include "Ast.hpp"

struct StringLiteralNode : public ASTNode {
  std::string value;
  explicit StringLiteralNode(std::string v) : value(std::move(v)) {}
  LanguagePrimitives execute(Environment &) override { return value; }

  std::string toString() const override { return "\"" + value + "\""; }
};