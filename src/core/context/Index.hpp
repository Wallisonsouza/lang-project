#pragma once
#include <memory>
#include <unordered_map>

namespace lang::core {
template <typename Key, typename T> class Index {
  std::unordered_map<Key, std::shared_ptr<T>> table;

public:
  void add(const Key &key, std::shared_ptr<T> obj) {
    table.emplace(key, std::move(obj));
  }

  std::shared_ptr<T> get(const Key &key) const {
    auto it = table.find(key);
    return it != table.end() ? it->second : nullptr;
  }

  bool contains(const Key &key) const { return table.find(key) != table.end(); }
};

} // namespace lang::core
