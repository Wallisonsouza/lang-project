#pragma once
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include <string>

namespace parser::node {

struct NumberLiteralNode : core::ast::ASTExpressionNode {
  double value;

  explicit NumberLiteralNode(double v) : core::ast::ASTExpressionNode(core::ast::NodeKind::NumberLiteral), value(v) {}
};

struct StringLiteralNode : core::ast::ASTExpressionNode {
  std::string value;

  explicit StringLiteralNode(std::string v) : ASTExpressionNode(core::ast::NodeKind::StringLiteral), value(std::move(v)) {}
};

struct BoolLiteralNode : core::ast::ASTExpressionNode {
  bool value;

  explicit BoolLiteralNode(bool v) : ASTExpressionNode(core::ast::NodeKind::BooleanLiteral), value(v) {}
};

struct CharLiteralNode : core::ast::ASTExpressionNode {
  char32_t value;

  explicit CharLiteralNode(char32_t v) : ASTExpressionNode(core::ast::NodeKind::CharLiteral), value(v) {}
};

struct NullLiteralNode : core::ast::ASTExpressionNode {
  NullLiteralNode() : ASTExpressionNode(core::ast::NodeKind::NullLiteral) {}
};

} // namespace parser::node
