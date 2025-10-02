#pragma once
#include "core/base/Entry.hpp"
#include <algorithm>
#include <vector>

template <typename T> class Context {
public:
  Context() = default;

  void addContext(int priority, std::unique_ptr<T> handler) {
    handlers.push_back({priority, std::move(handler)});
    std::sort(handlers.begin(), handlers.end(), [](const Entry<T> &a, const Entry<T> &b) { return a.priority < b.priority; });
  }
  const std::vector<Entry<T>> &getAllEntries() const { return handlers; }

private:
  std::vector<Entry<T>> handlers;
};