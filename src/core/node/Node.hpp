#pragma once

#include "NodeKind.hpp"
#include <string>

namespace core::node {

struct Node {
  NodeKind kind;
  bool has_error = false;
  virtual std::string to_string() { return "NOT_STRING_IMPLEMENTATION"; }

protected:
  explicit Node(NodeKind k) : kind(k) {}
};

} // namespace core::node
