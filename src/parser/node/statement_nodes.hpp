#pragma once
#include "core/node/Type.hpp"
#include "parser/node/modifier.hpp"
#include "parser/node/type_nodes.hpp"

namespace node {

struct IfStatementNode : core::node::StatementNode {
  core::node::ExpressionNode *condition;
  std::vector<core::node::StatementNode *> then_body;
  std::vector<core::node::StatementNode *> else_body;
};

struct BlockNode : core::node::StatementNode {
  std::vector<core::node::StatementNode *> statements;

  explicit BlockNode(std::vector<core::node::StatementNode *> stmts = {}) : statements(std::move(stmts)) {}
};

struct FunctionParameterNode : public core::node::StatementNode {
  std::u32string name;
  TypeNode *type;
  core::node::ExpressionNode *value = nullptr;
  bool has_error = false;

  FunctionParameterNode(std::u32string n, TypeNode *t, core::node::ExpressionNode *v) : name(std::move(n)), type(t), value(v) {}
};

struct VariableDeclarationNode : core::node::StatementNode {
  std::u32string name;
  TypeNode *type;
  core::node::ExpressionNode *value;
  Modifier modifiers;

  VariableDeclarationNode(std::u32string n, TypeNode *t, core::node::ExpressionNode *v, Modifier modifiers = Modifier::None) : name(std::move(n)), type(t), value(v), modifiers(modifiers) {}
};

struct FunctionDeclarationNode : core::node::StatementNode {
  std::u32string name;
  std::vector<FunctionParameterNode *> parameters;
  TypeNode *return_type;
  BlockNode *body;
  Modifier modifiers;

  FunctionDeclarationNode(std::u32string n, std::vector<FunctionParameterNode *> params, TypeNode *ret_type = nullptr, BlockNode *b = nullptr, Modifier mods = Modifier::None)
      : name(std::move(n)), parameters(std::move(params)), return_type(ret_type), body(b), modifiers(mods) {}
};

} // namespace node