#pragma once
#include "core/node/Node.hpp"
#include <string>
#include <vector>

namespace node {
struct TypeNode : core::node::Node {
  std::u32string name;
  std::vector<TypeNode *> generics;
  bool is_primitive = false;

  explicit TypeNode(std::u32string n, bool is_primitive) : name(std::move(n)), is_primitive(is_primitive) {}

  TypeNode(std::u32string n, std::vector<TypeNode *> g) : name(std::move(n)), generics(std::move(g)) {}
};

struct VoidTypeNode : TypeNode {
  VoidTypeNode() : TypeNode(U"void", true) {}
};

} // namespace node