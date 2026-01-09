#pragma once
#include "core/node/Type.hpp"
#include <optional>
#include <string>
#include <vector>

namespace parser::node::statement {

struct PathExprNode : core::node::ExpressionNode {
  std::vector<core::node::IdentifierNode *> segments;
  SymbolId symbol_id = SIZE_MAX;

  explicit PathExprNode(std::vector<core::node::IdentifierNode *> segs) : ExpressionNode(core::node::NodeKind::PathExpression), segments(std::move(segs)) {}
};

struct ImportNode : core::node::StatementNode {
  std::vector<core::node::IdentifierNode *> path;
  std::optional<std::string> alias;

  explicit ImportNode(std::vector<core::node::IdentifierNode *> p) : StatementNode(core::node::NodeKind::Import), path(std::move(p)) {}
};

struct AssignmentNode : core::node::ExpressionNode {
  core::node::ExpressionNode *target;
  core::node::ExpressionNode *value;

  AssignmentNode(core::node::ExpressionNode *t, core::node::ExpressionNode *v) : ExpressionNode(core::node::NodeKind::Assignment), target(t), value(v) {}
};

} // namespace parser::node::statement
