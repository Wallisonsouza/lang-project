#pragma once
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include <string>
#include <vector>

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

template <typename T> struct ListNode : core::ast::ASTExpressionNode {
  std::vector<T *> elements;
  ListNode(core::ast::NodeKind kind, std::vector<T *> elems) : ASTExpressionNode(kind), elements(std::move(elems)) {}
};

struct ASTParameterListNode : ListNode<core::ast::PatternNode> {
  explicit ASTParameterListNode(std::vector<core::ast::PatternNode *> elems) : ListNode(core::ast::NodeKind::ParameterList, std::move(elems)) {}
};

struct ASTArrayLiteralNode : ListNode<core::ast::ASTExpressionNode> {
  explicit ASTArrayLiteralNode(std::vector<core::ast::ASTExpressionNode *> elems) : ListNode(core::ast::NodeKind::ArrayLiteral, std::move(elems)) {}
};

} // namespace parser::node
