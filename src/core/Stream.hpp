#pragma once
#include "Stack.hpp"
#include "errors/StreamErrors.hpp"
#include <cstddef>
#include <vector>

template <typename T> class Stream {
public:
  explicit Stream(const std::vector<T> &values) : values(values) {}
  explicit Stream(std::vector<T> &&values) : values(std::move(values)) {}

  template <typename Predicate> std::string readWhileString(Predicate pred) {
    std::string result;
    while (hasNext() && pred(current())) {
      result += advance();
    }
    return result;
  }

  T &advance() {
    if (!hasNext())
      throw StreamEndException();
    T &val = values[stack.getPosition()];
    stack.advance();
    return val;
  }

  const T &current() const {

    if (!hasNext()) {
      throw StreamEndException();
    }

    return values[stack.getPosition()];
  }

  const T &previous() const {
    size_t pos = stack.getPosition();
    if (pos == 0) {
      throw StreamBeginException();
    }

    return values[pos - 1];
  }

  const T &peek(size_t offset = 0) const {
    size_t target = stack.getPosition() + offset;
    if (target >= values.size())
      throw StreamEndException();
    return values[target];
  }

  bool hasNext() const { return stack.getPosition() < values.size(); }

  void saveState() { stack.save(); }
  void rollback() { stack.restore(); }

  size_t position() const { return stack.getPosition(); }

private:
  std::vector<T> values;
  Stack stack;
};
