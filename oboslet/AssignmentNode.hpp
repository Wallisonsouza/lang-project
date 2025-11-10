  // #pragma once
  // #include "core/ast.hpp"

  // struct AssignmentNode : public Node<Node<void>> {
  //   std::string name;

  //   AssignmentNode(std::string n, std::unique_ptr<Node> val) : name(std::move(n)) { 
  //     value = std::move(val)
  //   }

  //   std::string toString() const override { return "AssignmentNode { name: \"" + name + "\", value: " + value->toString() + " }"; }
  // };