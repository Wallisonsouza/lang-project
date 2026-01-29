#pragma once
#include "core/node/BinaryOp.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"

namespace parser::node {

struct BinaryExpressionNode : core::ast::ASTExpressionNode {

  core::ast::ASTExpressionNode *left;
  core::ast::BinaryOperation op;
  core::ast::ASTExpressionNode *right;

  BinaryExpressionNode(core::ast::ASTExpressionNode *l, core::ast::BinaryOperation o, core::ast::ASTExpressionNode *r)
      : ASTExpressionNode(core::ast::NodeKind::BinaryExpression), left(l), op(o), right(r) {}
};

} // namespace parser::node
