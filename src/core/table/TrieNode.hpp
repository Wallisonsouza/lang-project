#pragma once
#include <string_view>
#include <unordered_map>
#include <vector>

template <typename T> struct TrieNode {
  bool is_terminal = false;
  T *value = nullptr;
  std::unordered_map<char32_t, TrieNode *> children;
};

template <typename T> class Trie {
private:
  TrieNode<T> root_;
  std::vector<TrieNode<T>> pool_;

  TrieNode<T> *create_node() {
    pool_.emplace_back();
    return &pool_.back();
  }

public:
  Trie() { pool_.reserve(256); }

  void clear() {
    root_ = TrieNode<T>{};
    pool_.clear();
  }

  void insert(const std::u32string_view &key, T *value) {
    TrieNode<T> *node = &root_;
    for (char32_t ch : key) {
      auto it = node->children.find(ch);
      if (it == node->children.end()) {
        TrieNode<T> *new_node = create_node();
        node->children[ch] = new_node;
        node = new_node;
      } else {
        node = it->second;
      }
    }
    node->is_terminal = true;
    node->value = value;
  }

  bool has_prefix(const std::u32string_view &prefix) const {
    const TrieNode<T> *node = &root_;
    for (char32_t ch : prefix) {
      auto it = node->children.find(ch);
      if (it == node->children.end()) return false;
      node = it->second;
    }
    return true;
  }

  T *lookup(const std::u32string_view &key) const {
    const TrieNode<T> *node = &root_;
    for (char32_t ch : key) {
      auto it = node->children.find(ch);
      if (it == node->children.end()) return nullptr;
      node = it->second;
    }
    return node->is_terminal ? node->value : nullptr;
  }
};
