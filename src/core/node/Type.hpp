#pragma once
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include "core/node/Modifier.hpp"
#include "core/node/Node.hpp"
#include "core/node/NodeKind.hpp"
#include "core/token/Location.hpp"
#include <string>
#include <vector>
struct Value;

namespace core::node {

struct StatementNode : Node {
  explicit StatementNode(NodeKind k) : Node(NodeKindBase::Statement, k) {}
};

struct ExpressionNode : Node {
  explicit ExpressionNode(NodeKind k) : Node(NodeKindBase::Expression, k) {}
};

struct ExpressionStatementNode : StatementNode {
  ExpressionNode *expr;

  explicit ExpressionStatementNode(ExpressionNode *expr)
      : StatementNode(NodeKind::ExpressionStatement), expr(expr) {}
};

struct TypeDeclarationNode : StatementNode {
  std::string name;
  std::vector<std::string> type_params;

  explicit TypeDeclarationNode(std::string n,
                               std::vector<std::string> params = {})
      : StatementNode(NodeKind::TypeDeclaration), name(std::move(n)),
        type_params(std::move(params)) {}
};

struct IdentifierNode : core::node::ExpressionNode {
  std::string name;
  SymbolId symbol_id = SIZE_MAX;

  explicit IdentifierNode(std::string n, const SourceSlice &slice = {})
      : ExpressionNode(core::node::NodeKind::Identifier), name(std::move(n)) {
    this->slice = slice;
  }
};

struct TypeNode : core::node::Node {
  IdentifierNode *id;
  const std::vector<TypeNode *> generics;
  bool is_primitive = false;
  SymbolId symbol_id = SIZE_MAX;

  explicit TypeNode(IdentifierNode *id, bool primitive = false)
      : Node(NodeKindBase::Type, core::node::NodeKind::Type), id(id),
        is_primitive(primitive) {}

  TypeNode(IdentifierNode *id, std::vector<TypeNode *> g)
      : Node(NodeKindBase::Type, core::node::NodeKind::Type), id(id),
        generics(std::move(g)) {}

  static bool is_same_type(TypeNode *a, TypeNode *b) {
    if (a->is_primitive && b->is_primitive) {
      return a->id->name == b->id->name;
    }

    if (a->id->name != b->id->name)
      return false;
    if (a->generics.size() != b->generics.size())
      return false;
    for (size_t i = 0; i < a->generics.size(); i++) {
      if (!is_same_type(a->generics[i], b->generics[i]))
        return false;
    }
    return true;
  }
};

struct PatternNode : StatementNode {
  core::node::IdentifierNode *identifier;
  core::node::TypeNode *type;
  core::node::ExpressionNode *value;
  core::node::Modifiers modifiers;
  SymbolId symbol_id = SIZE_MAX;

  PatternNode(core::node::IdentifierNode *n, core::node::TypeNode *t,
              core::node::ExpressionNode *v,
              core::node::Modifiers modifiers = {})
      : StatementNode(core::node::NodeKind::VariableDeclaration), identifier(n),
        type(t), value(v), modifiers(modifiers) {}
};

struct PatternErrorNode : PatternNode {
  PatternErrorNode(const SourceSlice &expected_slice,
                   core::node::Modifiers modifiers = {})
      : PatternNode(nullptr, nullptr, nullptr, modifiers) {
    this->kind = core::node::NodeKind::Error;
    this->slice = expected_slice;

    flags |= NodeFlags::HasError;

    this->slice = expected_slice;
  }
};

struct ParameterListNode : Node {
  std::vector<PatternNode *> parameters;

  explicit ParameterListNode(std::vector<PatternNode *> params = {})
      : Node(NodeKindBase::Unknown, core::node::NodeKind::ParameterList),
        parameters(std::move(params)) {}
};

struct NativeFunctionDeclarationNode : StatementNode {
  IdentifierNode *identifier;
  std::vector<PatternNode *> params;
  node::TypeNode *return_type;
  SymbolId symbol_id;

  Value::NativeFunction callback;

  // Construtor
  NativeFunctionDeclarationNode(IdentifierNode *id,
                                std::vector<PatternNode *> p,
                                node::TypeNode *ret, Value::NativeFunction cb)
      : StatementNode(core::node::NodeKind::NativeFunctionDeclaration),
        identifier(id), params(std::move(p)), return_type(ret),
        callback(std::move(cb)) {}
};

} // namespace core::node
