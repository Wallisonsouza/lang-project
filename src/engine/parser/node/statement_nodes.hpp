#pragma once

#include "core/node/Modifier.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"

namespace parser::node {

struct BlockStatementNode : core::node::StatementNode {
  std::vector<core::node::StatementNode *> statements;

  explicit BlockStatementNode(std::vector<core::node::StatementNode *> stmts = {}) : StatementNode(core::node::NodeKind::BlockStatement), statements(std::move(stmts)) {}
};

struct IfStatementNode : core::node::StatementNode {
  core::node::ExpressionNode *condition;
  BlockStatementNode *if_block;
  BlockStatementNode *else_block;

  IfStatementNode(core::node::ExpressionNode *cond, BlockStatementNode *then_b, BlockStatementNode *else_b = nullptr)
      : core::node::StatementNode(core::node::NodeKind::IfStatement), condition(cond), if_block(then_b), else_block(else_b) {}
};

struct VariableDeclarationNode : core::node::StatementNode {
  core::node::IdentifierNode *identifier;
  core::node::TypeNode *type;
  core::node::ExpressionNode *value;
  core::node::Modifiers modifiers;
  SymbolId symbol_id = SIZE_MAX;

  VariableDeclarationNode(core::node::IdentifierNode *n, core::node::TypeNode *t, core::node::ExpressionNode *v, core::node::Modifiers modifiers = {})
      : StatementNode(core::node::NodeKind::VariableDeclaration), identifier(n), type(t), value(v), modifiers(modifiers) {}
};

struct FunctionDeclarationNode : core::node::StatementNode {
  core::node::IdentifierNode *identifier;
  std::vector<core::node::FunctionParameterNode *> params;
  core::node::TypeNode *return_type;
  BlockStatementNode *body;
  core::node::Modifiers modifiers;
  SymbolId symbol_id = SIZE_MAX;

  FunctionDeclarationNode(core::node::IdentifierNode *identifier,
                          std::vector<core::node::FunctionParameterNode *> params,
                          core::node::TypeNode *ret_type = nullptr,
                          BlockStatementNode *b = nullptr,
                          core::node::Modifiers mods = {})
      : StatementNode(core::node::NodeKind::FunctionDeclaration), identifier(identifier), params(std::move(params)), return_type(ret_type), body(b), modifiers(mods) {}
};

struct MemberAccessNode : core::node::ExpressionNode {
  core::node::ExpressionNode *object;
  core::node::ExpressionNode *property;

  MemberAccessNode(core::node::ExpressionNode *obj, core::node::ExpressionNode *prop) : ExpressionNode(core::node::NodeKind::MemberAccess), object(obj), property(prop) {}
};

struct IndexAccessNode : core::node::ExpressionNode {
  core::node::ExpressionNode *base;  // objeto ou array
  core::node::ExpressionNode *index; // índice ou expressão de acesso

  IndexAccessNode(core::node::ExpressionNode *b, core::node::ExpressionNode *i) : ExpressionNode(core::node::NodeKind::IndexAccess), base(b), index(i) {}
};

struct FunctionCallNode : core::node::ExpressionNode {
  core::node::ExpressionNode *callee;
  std::vector<core::node::ExpressionNode *> args;
  SymbolId symbol_id = SIZE_MAX;
  FunctionCallNode(core::node::ExpressionNode *c, std::vector<core::node::ExpressionNode *> a) : ExpressionNode(core::node::NodeKind::FunctionCall), callee(c), args(std::move(a)) {}
};

struct OperatorDeclarationNode : core::node::StatementNode {
  core::token::TokenKind operator_kind; // +, -, *, ==, etc

  std::vector<core::node::FunctionParameterNode *> parameters;
  core::node::TypeNode *return_type;
  BlockStatementNode *body;

  core::node::Modifier modifiers;
  SymbolId symbol_id = SIZE_MAX;

  OperatorDeclarationNode(core::token::TokenKind op,
                          std::vector<core::node::FunctionParameterNode *> params,
                          core::node::TypeNode *ret_type = nullptr,
                          BlockStatementNode *b = nullptr,
                          core::node::Modifier mods = core::node::Modifier::None)
      : StatementNode(core::node::NodeKind::OperatorDeclaration), operator_kind(op), parameters(std::move(params)), return_type(ret_type), body(b), modifiers(mods) {}
};

struct ReturnStatementNode : core::node::StatementNode {
  core::node::ExpressionNode *value = nullptr;

  ReturnStatementNode(core::node::ExpressionNode *v) : StatementNode(core::node::NodeKind::ReturnStatement), value(v) {}
};
} // namespace parser::node