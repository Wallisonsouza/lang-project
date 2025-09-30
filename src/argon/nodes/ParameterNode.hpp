#pragma once
#include "core/ast.hpp"

struct ParameterNode : public ASTNode {
  std::string name;
  std::unique_ptr<ASTNode> defaultValue;

  ParameterNode(std::string n, std::unique_ptr<ASTNode> def = nullptr) : name(std::move(n)), defaultValue(std::move(def)) {}

  std::string toString() const override {
    if (defaultValue)
      return name + " = " + defaultValue->toString();
    return name;
  }
  LanguagePrimitives execute(Environment &) override { return {}; }
};