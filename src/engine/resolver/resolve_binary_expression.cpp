#include "engine/resolver/Resolver.hpp"

void Resolver::resolve_binary_expression(parser::node::BinaryExpressionNode *node) {
  resolve(node->left);
  resolve(node->right);
}
