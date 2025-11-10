#pragma once
#include <memory>
#include <vector>

namespace lang::core {

template <typename T> class Context {
  std::vector<std::shared_ptr<T>> objects;

public:
  void add(std::shared_ptr<T> obj) { objects.push_back(std::move(obj)); }

  const std::vector<std::shared_ptr<T>> &all() const { return objects; }
};

} // namespace lang::core
