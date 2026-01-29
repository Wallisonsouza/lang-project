#pragma once
#include "core/node/Type.hpp"
#include <optional>
#include <string>
#include <vector>

namespace parser::node::statement {

struct PathExprNode : core::ast::ASTExpressionNode {
  core::ast::ASTExpressionNode *base;
  core::ast::ASTExpressionNode *field;

  SymbolId symbol_id = SIZE_MAX;

  PathExprNode(core::ast::ASTExpressionNode *b, core::ast::ASTExpressionNode *f) : core::ast::ASTExpressionNode(core::ast::NodeKind::PathExpression), base(b), field(f) {}
};

struct ImportNode : core::ast::ASTStatementNode {
  std::vector<core::ast::IdentifierNode *> path;
  std::optional<std::string> alias;

  explicit ImportNode(std::vector<core::ast::IdentifierNode *> p) : ASTStatementNode(core::ast::NodeKind::Import), path(std::move(p)) {}
};

struct AssignmentNode : core::ast::ASTExpressionNode {
  core::ast::ASTExpressionNode *target;
  core::ast::ASTExpressionNode *value;

  AssignmentNode(core::ast::ASTExpressionNode *t, core::ast::ASTExpressionNode *v) : ASTExpressionNode(core::ast::NodeKind::Assignment), target(t), value(v) {}
};

} // namespace parser::node::statement
