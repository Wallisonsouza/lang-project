#pragma once
#include "core/node/Type.hpp"
#include <string>

namespace node {
struct NumberLiteralNode : core::node::ExpressionNode {
  double value;
  explicit NumberLiteralNode(double v) : value(v) {}
};

struct StringLiteralNode : core::node::ExpressionNode {
  std::u32string value;
  explicit StringLiteralNode(std::u32string v) : value(std::move(v)) {}
};

struct IdentifierNode : core::node::ExpressionNode {
  std::u32string name;
  explicit IdentifierNode(std::u32string n) : name(std::move(n)) {}
};

struct NullLiteralNode : core::node::ExpressionNode {};

struct BoolLiteralNode : core::node::ExpressionNode {
  bool value;
  explicit BoolLiteralNode(bool v) : value(v) {}
};

struct CharLiteralNode : core::node::ExpressionNode {
  char32_t value;
  explicit CharLiteralNode(char32_t v) : value(v) {}
};

} // namespace node