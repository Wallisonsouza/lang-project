#pragma once
#include "core/Arena.hpp"
#include "core/token/Token.hpp"
#include <functional>
#include <vector>

class TokenStream {
public:
  TokenStream() = default;

  template <typename T, typename... Args> T *create_token(Args &&...args) {
    T *tok = arena_.create<T>(std::forward<Args>(args)...);
    tokens_.push_back(tok);
    return tok;
  }

  void traverse(const std::function<void(core::token::Token *)> &fn) const {
    for (auto *tok : tokens_) fn(tok);
  }

  size_t size() const { return tokens_.size(); }

  core::token::Token *operator[](size_t idx) const { return tokens_[idx]; }

  const std::vector<core::token::Token *> &get_tokens() const { return tokens_; }

private:
  core::memory::Arena arena_;
  std::vector<core::token::Token *> tokens_;
};
