#pragma once
#include "core/ast.hpp"

struct AssignmentNode : public Node {
  std::string name;
  std::unique_ptr<Node> value;

  AssignmentNode(std::string n, std::unique_ptr<Node> val) : name(std::move(n)), value(std::move(val)) {}

  std::string toString() const override { return "AssignmentNode { name: \"" + name + "\", value: " + value->toString() + " }"; }
};
