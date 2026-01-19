#pragma once

#include "NodeKind.hpp"
#include "core/node/flags.hpp"
#include "core/token/Location.hpp"
#include <string>
#include <vector>

namespace core::node {

struct Node;

struct ChildGroup {
  const char *label;
  std::vector<Node *> children;
};

struct Node {
  NodeKind kind;
  NodeKindBase base_kind;
  SourceSlice slice;
  NodeFlags flags = NodeFlags::None;

  virtual ~Node() = default;

  virtual std::string to_string_node() { return "NOT_STRING_IMPLEMENTATION"; }

  virtual std::vector<ChildGroup> child_groups() const { return {}; }

protected:
  explicit Node(NodeKindBase base, NodeKind k) : base_kind(base), kind(k) {}
};

} // namespace core::node
