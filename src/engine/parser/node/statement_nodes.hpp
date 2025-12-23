#pragma once
#include "core/node/Modifier.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"

namespace parser::node {

struct IfStatementNode : core::node::StatementNode {
  core::node::ExpressionNode *condition;
  std::vector<core::node::StatementNode *> then_body;
  std::vector<core::node::StatementNode *> else_body;

  IfStatementNode() : StatementNode(core::node::NodeKind::IfStatement) {}
};

struct BlockNode : core::node::StatementNode {
  std::vector<core::node::StatementNode *> statements;

  explicit BlockNode(std::vector<core::node::StatementNode *> stmts = {})
      : StatementNode(core::node::NodeKind::Block),
        statements(std::move(stmts)) {}
};

struct VariableDeclarationNode : core::node::StatementNode {
  std::u32string name;
  core::node::TypeNode *type;
  core::node::ExpressionNode *value;
  core::node::Modifier modifiers;
  core::Symbol *symbol = nullptr;

  VariableDeclarationNode(
      std::u32string n, core::node::TypeNode *t, core::node::ExpressionNode *v,
      core::node::Modifier modifiers = core::node::Modifier::None)
      : StatementNode(core::node::NodeKind::VariableDeclaration),
        name(std::move(n)), type(t), value(v), modifiers(modifiers) {}
};

struct FunctionParameterNode : core::node::StatementNode {
  std::u32string name;
  core::node::TypeNode *type;
  core::node::ExpressionNode *value = nullptr;
  core::Symbol *symbol = nullptr;
  bool has_error = false;

  FunctionParameterNode(std::u32string n, core::node::TypeNode *t,
                        core::node::ExpressionNode *v)
      : StatementNode(core::node::NodeKind::FunctionParameter),
        name(std::move(n)), type(t), value(v) {}
};

struct FunctionDeclarationNode : core::node::StatementNode {
  std::u32string name;
  std::vector<FunctionParameterNode *> params;
  core::node::TypeNode *return_type;
  BlockNode *body;
  core::node::Modifier modifiers;
  core::Symbol *symbol = nullptr;

  FunctionDeclarationNode(
      std::u32string n, std::vector<FunctionParameterNode *> params,
      core::node::TypeNode *ret_type = nullptr, BlockNode *b = nullptr,
      core::node::Modifier mods = core::node::Modifier::None)
      : StatementNode(core::node::NodeKind::FunctionDeclaration),
        name(std::move(n)), params(std::move(params)), return_type(ret_type),
        body(b), modifiers(mods) {}
};

struct FunctionCallNode : core::node::ExpressionNode {
  core::node::ExpressionNode *callee;
  std::vector<core::node::ExpressionNode *> args;
  core::Symbol *symbol = nullptr;
  FunctionCallNode(core::node::ExpressionNode *c,
                   std::vector<core::node::ExpressionNode *> a)
      : ExpressionNode(core::node::NodeKind::FunctionCall), callee(c),
        args(std::move(a)) {}
};

struct OperatorDeclarationNode : core::node::StatementNode {
  core::token::TokenKind operator_kind; // +, -, *, ==, etc

  std::vector<FunctionParameterNode *> parameters;
  core::node::TypeNode *return_type;
  BlockNode *body;

  core::node::Modifier modifiers;
  core::Symbol *symbol = nullptr;

  OperatorDeclarationNode(
      core::token::TokenKind op, std::vector<FunctionParameterNode *> params,
      core::node::TypeNode *ret_type = nullptr, BlockNode *b = nullptr,
      core::node::Modifier mods = core::node::Modifier::None)
      : StatementNode(core::node::NodeKind::OperatorDeclaration),
        operator_kind(op), parameters(std::move(params)), return_type(ret_type),
        body(b), modifiers(mods) {}
};

struct ReturnStatementNode : core::node::StatementNode {
  core::node::ExpressionNode *value = nullptr;

  ReturnStatementNode(core::node::ExpressionNode *v)
      : StatementNode(core::node::NodeKind::ReturnStatement), value(v) {}
};

} // namespace parser::node