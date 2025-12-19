#include "core/node/Type.hpp"
namespace node {
struct BinaryExpressionNode : core::node::ExpressionNode {
  core::node::ExpressionNode *left;
  std::u32string op;
  core::node::ExpressionNode *right;

  BinaryExpressionNode(core::node::ExpressionNode *l, std::u32string o, core::node::ExpressionNode *r) : left(l), op(std::move(o)), right(r) {}
};

} // namespace node