#pragma once
#include <cstddef>
#include <optional>
#include <vector>

namespace utils {

template <typename T> class Stream {
  const std::vector<T> &data_;
  size_t pos_ = 0;
  std::vector<size_t> checkpoint_stack_;

public:
  explicit Stream(const std::vector<T> &input) : data_(input) {}

  // -----------------------------
  // Acesso e posição
  // -----------------------------
  inline bool is_end() const noexcept { return pos_ >= data_.size(); }
  inline bool has(size_t offset = 0) const noexcept { return pos_ + offset < data_.size(); }
  inline size_t current_pos() const noexcept { return pos_; }

  inline T current() const noexcept { return has() ? data_[pos_] : T{}; }
  inline T peek(size_t offset = 0) const noexcept { return has(offset) ? data_[pos_ + offset] : nullptr; }

  // -----------------------------
  // Consumo e avanço
  // -----------------------------
  inline T consume() noexcept { return is_end() ? T{} : data_[pos_++]; }

  inline void advance(size_t count = 1) noexcept { pos_ = (pos_ + count <= data_.size()) ? pos_ + count : data_.size(); }

  inline void reset(size_t p) noexcept { pos_ = (p <= data_.size()) ? p : data_.size(); }

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
    if (!checkpoint_stack_.empty()) checkpoint_stack_.pop_back();
  }

  // -----------------------------
  // Busca simples
  // -----------------------------
  inline std::optional<size_t> index_of(const T &item) const noexcept {
    for (size_t i = 0; i < data_.size(); ++i) {
      if (data_[i] == item) return i;
    }
    return std::nullopt;
  }
};

} // namespace utils
