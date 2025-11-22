#pragma once
#include "core/token/TokenDescriptor.hpp"
#include <memory>
#include <string>
#include <unordered_map>

struct TrieNode {
  bool is_terminal       = false;
  TokenDescriptor *token = nullptr;

  std::unordered_map<char32_t, std::unique_ptr<TrieNode>> next;
};

class TokenTrie {
private:
  std::unique_ptr<TrieNode> root = std::make_unique<TrieNode>();

public:
  void clear() { root = std::make_unique<TrieNode>(); }

  void insert(const std::u32string &name, TokenDescriptor *token) {
    TrieNode *node = root.get();

    for (char32_t ch : name) {
      if (!node->next.count(ch)) {
        node->next[ch] = std::make_unique<TrieNode>();
      }
      node = node->next[ch].get();
    }

    node->is_terminal = true;
    node->token       = token;
  }

  bool has_prefix(const std::u32string &prefix) const {
    const TrieNode *node = root.get();

    for (char32_t ch : prefix) {
      if (!node->next.count(ch))
        return false;
      node = node->next.at(ch).get();
    }

    return true;
  }

  TokenDescriptor *lookup(const std::u32string &name) const {
    const TrieNode *node = root.get();

    for (char32_t ch : name) {
      if (!node->next.count(ch))
        return nullptr;
      node = node->next.at(ch).get();
    }

    return node->is_terminal ? node->token : nullptr;
  }
};
