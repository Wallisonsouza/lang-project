#pragma once

#include "NodeKind.hpp"
#include "core/token/Location.hpp"
#include <string>

namespace core::node {

struct Node {
  NodeKind kind;
  NodeKindBase base_kind;
  Slice slice;
  virtual std::string to_string_node() { return "NOT_STRING_IMPLEMENTATION"; }

protected:
  explicit Node(NodeKindBase base, NodeKind k) : base_kind(base), kind(k) {}
};

} // namespace core::node
