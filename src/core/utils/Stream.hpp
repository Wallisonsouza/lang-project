#pragma once
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

namespace lang::core {

template <typename T> class Stream {
  const std::vector<T> &data;
  size_t pos  = 0;
  size_t line = 0;

public:
  size_t get_current_line() const noexcept { return line; }

  explicit Stream(const std::vector<T> &input) : data(input) {}

  inline bool eof() const noexcept { return pos >= data.size(); }
  inline bool has(size_t offset = 0) const noexcept { return pos + offset < data.size(); }

  inline T current() const noexcept {

    assert(!eof());
    return data[pos];
  }

  inline T peek(size_t offset = 0) const noexcept {
    assert(has(offset));
    return data[pos + offset];
  }

  inline T consume() noexcept {
    assert(!eof());
    return data[pos++];
  }

  inline void advance(size_t count = 1) noexcept {
    pos += count;
    if (pos > data.size())
      pos = data.size();
  }

  inline size_t get_current_position() const noexcept { return pos; }
  inline void reset(size_t p) noexcept { pos = p; }

  inline std::u32string slice(size_t start, size_t end) const {
    assert(start <= end && end <= data.size());
    return std::u32string(data.begin() + start, data.begin() + end);
  }
};

} // namespace lang::core
