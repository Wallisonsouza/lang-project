#pragma once
#include "core/module/Symbol.hpp"
#include "core/node/Node.hpp"
#include <functional>
#include <string>
#include <vector>

namespace core::node {

struct StatementNode : Node {
protected:
  explicit StatementNode(NodeKind k) : Node(k) {}
};

struct ExpressionNode : Node {
protected:
  explicit ExpressionNode(NodeKind k) : Node(k) {}
};

struct TypeDeclarationNode : Node {
  std::u32string name;
  std::vector<std::u32string> type_params;

  explicit TypeDeclarationNode(std::u32string n,
                               std::vector<std::u32string> params = {})
      : Node(NodeKind::TypeDeclaration), name(std::move(n)),
        type_params(std::move(params)) {}
};

struct TypeNode : core::node::Node {
  std::u32string name;
  std::vector<TypeNode *> generics;
  bool is_primitive = false;
  core::Symbol *symbol = nullptr;

  explicit TypeNode(std::u32string n, bool primitive = false)
      : Node(core::node::NodeKind::Type), name(std::move(n)),
        is_primitive(primitive) {}

  TypeNode(std::u32string n, std::vector<TypeNode *> g)
      : Node(core::node::NodeKind::Type), name(std::move(n)),
        generics(std::move(g)) {}
};

struct VoidTypeNode : TypeNode {
  VoidTypeNode() : TypeNode(U"void", true) {
    kind = core::node::NodeKind::Type;
  }
};

struct NativeFunctionNode : core::node::StatementNode {
  std::u32string name;
  std::vector<node::TypeNode *> params;
  node::TypeNode *return_type;

  std::function<core::node::Node *(const std::vector<core::node::Node *> &)>
      callback;

  NativeFunctionNode(
      std::u32string n, std::vector<node::TypeNode *> p, node::TypeNode *ret,
      std::function<core::node::Node *(const std::vector<core::node::Node *> &)>
          cb)
      : StatementNode(core::node::NodeKind::NativeFunction), name(std::move(n)),
        params(std::move(p)), return_type(ret), callback(std::move(cb)) {}
};

} // namespace core::node
