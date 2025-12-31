#pragma once

#include "NodeKind.hpp"
#include "core/token/Location.hpp"
#include <string>

namespace core::node {

struct Node {
  NodeKind kind;
  Slice slice;
  virtual std::string to_string() { return "NOT_STRING_IMPLEMENTATION"; }

protected:
  explicit Node(NodeKind k) : kind(k) {}
};

} // namespace core::node
