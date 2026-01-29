#pragma once

#include "NodeKind.hpp"
#include "core/node/flags.hpp"
#include "core/token/Location.hpp"

namespace core::ast {

struct ASTNode {
  NodeKind kind;
  NodeKindBase base_kind;
  SourceSlice slice;
  NodeFlag flags;

  virtual ~ASTNode() = default;

protected:
  explicit ASTNode(NodeKindBase base, NodeKind k) : base_kind(base), kind(k) {}
};

} // namespace core::ast
