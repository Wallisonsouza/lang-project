#pragma once
#include "core/node/BinaryOp.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"

namespace parser::node {

struct BinaryExpressionNode : core::node::ExpressionNode {
  core::node::ExpressionNode *left;
  core::node::BinaryOp op;
  core::node::ExpressionNode *right;

  BinaryExpressionNode(core::node::ExpressionNode *l, core::node::BinaryOp o,
                       core::node::ExpressionNode *r)
      : ExpressionNode(core::node::NodeKind::BinaryExpression), left(l), op(o),
        right(r) {}
};

} // namespace parser::node
