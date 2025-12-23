#pragma once
#include "core/memory/Arena.hpp"
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
    for (auto *tok : tokens_)
      fn(tok);
  }

  size_t size() const { return tokens_.size(); }

  core::token::Token *operator[](size_t idx) const { return tokens_[idx]; }

  const std::vector<core::token::Token *> &get_tokens() const {
    return tokens_;
  }

public:
  size_t pos_ = 0;
  std::vector<size_t> checkpoint_stack_;
  // -----------------------------
  // Acesso e posição
  // -----------------------------
  inline bool is_end() const noexcept { return pos_ >= tokens_.size(); }
  inline bool has(size_t offset = 0) const noexcept {
    return pos_ + offset < tokens_.size();
  }
  inline size_t current_pos() const noexcept { return pos_; }

  inline core::token::Token *current() const noexcept {
    return has() ? tokens_[pos_] : nullptr;
  }
  inline core::token::Token *peek(size_t offset = 0) const noexcept {
    return has(offset) ? tokens_[pos_ + offset] : nullptr;
  }

  // -----------------------------
  // Consumo e avanço
  // -----------------------------
  inline core::token::Token *consume() noexcept {
    return is_end() ? nullptr : tokens_[pos_++];
  }

  inline void advance(size_t count = 1) noexcept {
    pos_ = (pos_ + count <= tokens_.size()) ? pos_ + count : tokens_.size();
  }

  inline void reset(size_t p) noexcept {
    pos_ = (p <= tokens_.size()) ? p : tokens_.size();
  }

  // -----------------------------
  // Checkpoints
  // -----------------------------
  inline void push_checkpoint() noexcept { checkpoint_stack_.push_back(pos_); }

  inline void rollback_checkpoint() noexcept {
    if (!checkpoint_stack_.empty()) {
      pos_ = checkpoint_stack_.back();
      checkpoint_stack_.pop_back();
    }
  }

  inline void discard_checkpoint() noexcept {
    if (!checkpoint_stack_.empty())
      checkpoint_stack_.pop_back();
  }

private:
  core::memory::Arena arena_;
  std::vector<core::token::Token *> tokens_;
};
