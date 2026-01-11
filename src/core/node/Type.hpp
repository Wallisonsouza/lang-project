#pragma once
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include "core/node/Node.hpp"
#include "core/node/NodeKind.hpp"
#include "core/token/Location.hpp"
#include <string>
#include <vector>

namespace core::node {

struct StatementNode : Node {
  explicit StatementNode(NodeKind k) : Node(NodeKindBase::Statement, k) {}
};

struct ExpressionNode : Node {
  explicit ExpressionNode(NodeKind k) : Node(NodeKindBase::Expression, k) {}
};

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expr;

  explicit ExpressionStatementNode(ExpressionNode *expr) : StatementNode(NodeKind::ExpressionStatement), expr(expr) {}
};

struct TypeDeclarationNode : StatementNode {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclarationNode(std::string n, std::vector<std::string> params = {}) : StatementNode(NodeKind::TypeDeclaration), name(std::move(n)), type_params(std::move(params)) {}
};

struct IdentifierNode : core::node::ExpressionNode {
  std::string name;
  SymbolId symbol_id = SIZE_MAX;

  explicit IdentifierNode(std::string n, const Slice &slice = {}) : ExpressionNode(core::node::NodeKind::Identifier), name(std::move(n)) { this->slice = slice; }
};

struct TypeNode : core::node::Node {
  IdentifierNode *id;
  const std::vector<TypeNode *> generics;
  bool is_primitive = false;
  SymbolId symbol_id = SIZE_MAX;

  explicit TypeNode(IdentifierNode *id, bool primitive = false) : Node(NodeKindBase::Type, core::node::NodeKind::Type), id(id), is_primitive(primitive) {}

  TypeNode(IdentifierNode *id, std::vector<TypeNode *> g) : Node(NodeKindBase::Type, core::node::NodeKind::Type), id(id), generics(std::move(g)) {}
};

struct VoidTypeNode : TypeNode {
  VoidTypeNode() : TypeNode(new IdentifierNode("void"), true) { kind = core::node::NodeKind::Type; }
};

struct NumberTypeNode : TypeNode {
  NumberTypeNode() : TypeNode(new IdentifierNode("number"), true) { kind = core::node::NodeKind::Type; }
};

struct FunctionParameterNode : StatementNode {
  IdentifierNode *identifier;
  core::node::TypeNode *type;
  core::node::ExpressionNode *value = nullptr;
  SymbolId symbol_id = SIZE_MAX;

  FunctionParameterNode(IdentifierNode *id, core::node::TypeNode *t, core::node::ExpressionNode *v) : StatementNode(core::node::NodeKind::FunctionParameter), identifier(id), type(t), value(v) {}
};

using native_callback = std::function<Value(const std::vector<Value> &)>;

struct NativeFunctionDeclarationNode : ExpressionNode {
  IdentifierNode *id;
  std::vector<FunctionParameterNode *> params;
  node::TypeNode *return_type;
  SymbolId symbol_id;

  native_callback callback;

  NativeFunctionDeclarationNode(IdentifierNode *id, std::vector<FunctionParameterNode *> p, node::TypeNode *ret, native_callback cb)
      : ExpressionNode(core::node::NodeKind::NativeFunctionDeclaration), id(id), params(std::move(p)), return_type(ret), callback(std::move(cb)) {}
};

} // namespace core::node
