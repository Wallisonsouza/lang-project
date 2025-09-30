#pragma once
#include "core/ast.hpp"

struct AssignmentNode : public ASTNode {
  std::string name;
  std::unique_ptr<ASTNode> value;

  AssignmentNode(std::string n, std::unique_ptr<ASTNode> val)
      : name(std::move(n)), value(std::move(val)) {}

  std::string toString() const override {
    return "AssignmentNode { name: \"" + name +
           "\", value: " + value->toString() + " }";
  }
};
