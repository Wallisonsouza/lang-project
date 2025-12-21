#pragma once
#include "core/Arena.hpp"
#include "core/node/Node.hpp"
#include <functional>

#pragma once
#include "core/Arena.hpp"
#include "core/node/Node.hpp"
#include <functional>
#include <vector>

class AST {
public:
  AST() = default;

  template <typename T, typename... Args> T *create_node(Args &&...args) {
    T *node = ast_arena.create<T>(std::forward<Args>(args)...);
    return node;
  }

  void traverse(const std::function<void(core::node::Node *)> &fn) const {
    for (auto *node : roots_)
      fn(node);
  }

  size_t size() const { return roots_.size(); }
  const std::vector<core::node::Node *> &get_nodes() const { return roots_; }

  void add_root(core::node::Node *node) { roots_.push_back(node); }

private:
  core::memory::Arena ast_arena;
  std::vector<core::node::Node *> roots_;
};
