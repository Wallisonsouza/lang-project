#pragma once
#include <cstddef>
#include <memory>
#include <vector>

namespace interpreter::core {

template <typename T> class Stream {
  const std::vector<std::shared_ptr<T>> &data;
  size_t pos = 0;

  // Checkpoints para backtracking
  std::vector<size_t> checkpointStack;

public:
  explicit Stream(const std::vector<std::shared_ptr<T>> &input) : data(input) {}

  inline bool eof() const noexcept { return pos >= data.size(); }
  inline bool has(size_t offset = 0) const noexcept { return pos + offset < data.size(); }

  inline size_t current_pos() const noexcept { return pos; }

  // ---------------------------------------------
  // CHECKPOINT
  // ---------------------------------------------
  inline void push() noexcept { checkpointStack.push_back(pos); }

  inline void pop_restore() noexcept {
    if (!checkpointStack.empty()) {
      pos = checkpointStack.back();
      checkpointStack.pop_back();
    }
  }

  inline void pop_discard() noexcept {
    if (!checkpointStack.empty()) checkpointStack.pop_back();
  }

  // ---------------------------------------------
  // ACESSO A ELEMENTOS (SEGURO)
  // ---------------------------------------------
  inline std::shared_ptr<T> current() const noexcept { return has() ? data[pos] : nullptr; }

  inline std::shared_ptr<T> peek(size_t offset = 0) const noexcept { return has(offset) ? data[pos + offset] : nullptr; }

  inline std::shared_ptr<T> consume() noexcept {
    if (eof()) return nullptr;
    return data[pos++];
  }

  inline ssize_t index_of(const std::shared_ptr<T> &item) const noexcept {
    for (size_t i = 0; i < data.size(); ++i) {
      if (data[i] == item) return static_cast<ssize_t>(i);
    }
    return -1;
  }

  inline void advance(size_t count = 1) noexcept {
    pos += count;
    if (pos > data.size()) pos = data.size();
  }

  inline void reset(size_t p) noexcept {
    if (p <= data.size()) pos = p;
  }

  // ---------------------------------------------
  // SLICE
  // ---------------------------------------------
  inline std::vector<std::shared_ptr<T>> slice(size_t start, size_t end) const noexcept {
    if (start > end || end > data.size()) return {};
    return std::vector<std::shared_ptr<T>>(data.begin() + start, data.begin() + end);
  }
};

} // namespace interpreter::core
