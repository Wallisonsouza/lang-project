#pragma once
#include <stack>
#include <string>

namespace lang::utils {

class TextStream {
  const std::u32string *data = nullptr;
  size_t index               = 0;
  std::stack<size_t> checkpoints;

public:
  explicit TextStream(const std::u32string &text) : data(&text), index(0) {}

  [[nodiscard]] bool has_next() const noexcept { return index < data->size(); }

  [[nodiscard]] const char32_t *current() const noexcept { return (index < data->size()) ? &(*data)[index] : nullptr; }

  [[nodiscard]] const char32_t *peek(size_t offset = 1) const noexcept {
    size_t next = index + offset;
    return (next < data->size()) ? &(*data)[next] : nullptr;
  }

  void advance(size_t count = 1) noexcept { index = (index + count <= data->size()) ? index + count : data->size(); }

  void retreat(size_t count = 1) noexcept { index = (count > index) ? 0 : index - count; }

  [[nodiscard]] size_t position() const noexcept { return index; }

  void seek(size_t pos) noexcept { index = (pos <= data->size()) ? pos : data->size(); }

  [[nodiscard]] std::u32string slice(size_t start, size_t endPos) const {
    if (start >= data->size())
      return U"";
    if (endPos > data->size())
      endPos = data->size();
    return data->substr(start, endPos - start);
  }

  void reset() noexcept { index = 0; }

  [[nodiscard]] bool eof() const noexcept { return index >= data->size(); }

  [[nodiscard]] size_t size() const noexcept { return data->size(); }

  // ---------- Save / Rollback / Commit ----------
  [[nodiscard]] size_t save() noexcept {
    checkpoints.push(index);
    return index;
  }

  void rollback() noexcept {
    if (!checkpoints.empty()) {
      index = checkpoints.top();
      checkpoints.pop();
    }
  }

  void rollback(size_t saved) noexcept {
    if (saved <= data->size())
      index = saved;
  }

  void commit() noexcept {
    if (!checkpoints.empty())
      checkpoints.pop();
  }
};

} // namespace lang::utils
