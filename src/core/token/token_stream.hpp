#pragma once
#include "core/memory/Arena.hpp"
#include "core/token/Token.hpp"
#include <functional>
#include <vector>

namespace core::token {
class TokenStream {
public:
  TokenStream() = default;

  template <typename T, typename... Args> T *create_token(Args &&...args) {
    T *tok = arena_.alloc<T>(std::forward<Args>(args)...);
    tokens_.push_back(tok);
    return tok;
  }

  void traverse(const std::function<void(core::token::Token *)> &fn) const {
    for (auto *tok : tokens_) fn(tok);
  }

  size_t size() const { return tokens_.size(); }

  core::token::Token *operator[](size_t idx) const { return tokens_[idx]; }

  const std::vector<core::token::Token *> &get_tokens() const { return tokens_; }

public:
  size_t pos_ = 0;
  std::vector<size_t> checkpoint_stack_;

  // -----------------------------
  // Acesso e posição
  // -----------------------------
  inline bool is_end() const noexcept { return pos_ >= tokens_.size(); }

  inline bool has(size_t offset = 0) const noexcept { return pos_ + offset < tokens_.size(); }

  inline size_t current_pos() const noexcept { return pos_; }

  inline core::token::Token *current() const noexcept { return has() ? tokens_[pos_] : nullptr; }

  inline core::token::Token *peek(size_t offset = 0) const noexcept { return has(offset) ? tokens_[pos_ + offset] : nullptr; }

  Token *match(TokenKind kind) {

    auto *token = peek();

    if (!token || !token->descriptor) return nullptr;

    if (token->descriptor->kind != kind) return nullptr;

    advance();
    return token;
  }

  inline const Slice &peek_slice(size_t offset = 0) const noexcept {
    static Slice empty{};

    if (auto *tok = peek(offset)) return tok->slice;

    return last_slice();
  }

  // -----------------------------
  // Consumo e avanço
  // -----------------------------
  inline core::token::Token *consume() noexcept {
    if (is_end()) return nullptr;
    last_token_ = tokens_[pos_];
    return tokens_[pos_++];
  }

  inline void advance(size_t count = 1) noexcept {
    while (count-- && pos_ < tokens_.size()) {
      last_token_ = tokens_[pos_];
      ++pos_;
    }
  }

  inline bool peek(TokenKind k, size_t offset = 0) const noexcept {
    auto *tok = peek(offset);
    return tok && tok->descriptor && tok->descriptor->kind == k;
  }

  inline void reset(size_t p) noexcept { pos_ = (p <= tokens_.size()) ? p : tokens_.size(); }

  // -----------------------------
  // Checkpoints
  // -----------------------------
  inline void add_checkpoint() noexcept { checkpoint_stack_.push_back(pos_); }

  inline void rollback_checkpoint() noexcept {
    if (!checkpoint_stack_.empty()) {
      pos_ = checkpoint_stack_.back();
      checkpoint_stack_.pop_back();
    }
  }

  inline void discard_checkpoint() noexcept {
    if (!checkpoint_stack_.empty()) checkpoint_stack_.pop_back();
  }

  // -----------------------------
  // Diagnóstico / Localização
  // -----------------------------
  inline const Slice &last_slice() const noexcept {
    static Slice empty{};
    return last_token_ ? last_token_->slice : empty;
  }

  inline const Slice slice_of(const Token *tok) const noexcept {
    static Slice empty{};
    return tok ? tok->slice : empty;
  }

private:
  core::memory::Arena arena_;
  std::vector<core::token::Token *> tokens_;
  core::token::Token *last_token_ = nullptr;
};

} // namespace core::token
