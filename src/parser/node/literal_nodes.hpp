#pragma once
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include <string>

namespace node {
struct NumberLiteralNode : core::node::ExpressionNode {
  double value;

  explicit NumberLiteralNode(double v)
      : ExpressionNode(core::node::NodeKind::NumberLiteral), value(v) {}
};

struct StringLiteralNode : core::node::ExpressionNode {
  std::u32string value;

  explicit StringLiteralNode(std::u32string v)
      : ExpressionNode(core::node::NodeKind::StringLiteral),
        value(std::move(v)) {}
};

struct BoolLiteralNode : core::node::ExpressionNode {
  bool value;

  explicit BoolLiteralNode(bool v)
      : ExpressionNode(core::node::NodeKind::BoolLiteral), value(v) {}
};

struct CharLiteralNode : core::node::ExpressionNode {
  char32_t value;

  explicit CharLiteralNode(char32_t v)
      : ExpressionNode(core::node::NodeKind::CharLiteral), value(v) {}
};

struct NullLiteralNode : core::node::ExpressionNode {
  NullLiteralNode() : ExpressionNode(core::node::NodeKind::NullLiteral) {}
};

struct IdentifierNode : core::node::ExpressionNode {
  std::u32string name;
  core::Symbol *symbol = nullptr;

  explicit IdentifierNode(std::u32string n)
      : ExpressionNode(core::node::NodeKind::Identifier), name(std::move(n)) {}
};

} // namespace node
