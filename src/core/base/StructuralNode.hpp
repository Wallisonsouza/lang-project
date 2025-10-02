#pragma once
#include <string>
struct StructuralNode {
  virtual ~StructuralNode() = default;
  virtual std::string toString() = 0;
};
