#pragma once
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include <string>

namespace parser::node {

struct NumberLiteralNode : core::node::ExpressionNode {
  double value;

  std::string to_string_node() override { return std::to_string(value); }

  explicit NumberLiteralNode(double v) : core::node::ExpressionNode(core::node::NodeKind::NumberLiteral), value(v) {}
};

struct StringLiteralNode : core::node::ExpressionNode {
  std::string value;

  std::string to_string_node() override { return value; }

  explicit StringLiteralNode(std::string v) : ExpressionNode(core::node::NodeKind::StringLiteral), value(std::move(v)) {}
};

struct BoolLiteralNode : core::node::ExpressionNode {
  bool value;

  explicit BoolLiteralNode(bool v) : ExpressionNode(core::node::NodeKind::BooleanLiteral), value(v) {}
};

struct CharLiteralNode : core::node::ExpressionNode {
  char32_t value;

  explicit CharLiteralNode(char32_t v) : ExpressionNode(core::node::NodeKind::CharLiteral), value(v) {}
};

struct NullLiteralNode : core::node::ExpressionNode {
  NullLiteralNode() : ExpressionNode(core::node::NodeKind::NullLiteral) {}
};

} // namespace parser::node
