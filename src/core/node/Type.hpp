#pragma once
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include "core/node/Node.hpp"
#include <string>
#include <vector>

namespace core::node {

struct StatementNode : Node {
  explicit StatementNode(NodeKind k) : Node(k) {}
};

struct ExpressionNode : Node {
  explicit ExpressionNode(NodeKind k) : Node(k) {}
};

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expr;

  explicit ExpressionStatementNode(ExpressionNode *expr) : StatementNode(NodeKind::ExpressionStatement), expr(expr) {}
};

struct TypeDeclarationNode : Node {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclarationNode(std::string n, std::vector<std::string> params = {}) : Node(NodeKind::TypeDeclaration), name(std::move(n)), type_params(std::move(params)) {}
};

struct TypeNode : core::node::Node {
  std::string name;
  std::vector<TypeNode *> generics;
  bool is_primitive = false;
  SymbolId symbol_id = SIZE_MAX;

  explicit TypeNode(std::string n, bool primitive = false) : Node(core::node::NodeKind::Type), name(std::move(n)), is_primitive(primitive) {}

  TypeNode(std::string n, std::vector<TypeNode *> g) : Node(core::node::NodeKind::Type), name(std::move(n)), generics(std::move(g)) {}
};

struct VoidTypeNode : TypeNode {
  VoidTypeNode() : TypeNode("void", true) { kind = core::node::NodeKind::Type; }
};

struct FunctionParameterNode : core::node::StatementNode {
  std::string name;
  core::node::TypeNode *type;
  core::node::ExpressionNode *value = nullptr;
  SymbolId symbol_id = SIZE_MAX;

  FunctionParameterNode(std::string n, core::node::TypeNode *t, core::node::ExpressionNode *v) : StatementNode(core::node::NodeKind::FunctionParameter), name(std::move(n)), type(t), value(v) {}
};

using native_callback = std::function<Value(const std::vector<Value> &)>;

struct NativeFunctionDeclarationNode : ExpressionNode {
  std::string name;
  std::vector<FunctionParameterNode *> params;
  node::TypeNode *return_type;

  native_callback callback;

  NativeFunctionDeclarationNode(std::string n, std::vector<FunctionParameterNode *> p, node::TypeNode *ret, native_callback cb)
      : ExpressionNode(core::node::NodeKind::NativeFunctionDeclaration), name(std::move(n)), params(std::move(p)), return_type(ret), callback(std::move(cb)) {}
};

} // namespace core::node
