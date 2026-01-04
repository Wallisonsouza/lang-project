#pragma once
#include "core/node/Type.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include <optional>
#include <string>
#include <vector>

namespace parser::node::statement {

struct PathExprNode : core::node::ExpressionNode {
  std::vector<IdentifierNode *> segments;
  SymbolId symbol_id = SIZE_MAX;

  explicit PathExprNode(std::vector<IdentifierNode *> segs)
      : ExpressionNode(core::node::NodeKind::PathExpr),
        segments(std::move(segs)) {}
};

struct ImportNode : core::node::StatementNode {
  std::vector<IdentifierNode *> path;
  std::optional<std::string> alias;

  explicit ImportNode(std::vector<IdentifierNode *> p)
      : StatementNode(core::node::NodeKind::Import), path(std::move(p)) {}
};

struct AssignmentNode : core::node::ExpressionNode {
  core::node::ExpressionNode *target;
  core::node::ExpressionNode *value;

  AssignmentNode(core::node::ExpressionNode *t, core::node::ExpressionNode *v)
      : ExpressionNode(core::node::NodeKind::Assignment), target(t), value(v) {}
};

} // namespace parser::node::statement
