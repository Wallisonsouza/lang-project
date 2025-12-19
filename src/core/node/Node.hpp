#pragma once

namespace core::node {
struct Node {
  virtual ~Node() = default;
  bool has_error = false;
};
} // namespace core::node