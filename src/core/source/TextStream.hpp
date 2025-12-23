#pragma once
#include "SourceBuffer.hpp"
#include "Span.hpp"
#include "core/token/Location.hpp"
#include <cstddef>
#include <vector>

namespace core::source {
class TextStream {
public:
  struct State {
    const char32_t *ptr;
    size_t offset;
    size_t line;
    size_t column;

    Span span_to(const State &end) const { return Span{ptr, end.ptr}; }

    SourceRange range_to(const State &end) const {
      return SourceRange{.begin = {offset, line, column},
                         .end = {end.offset, end.line, end.column}};
    }
  };

private:
  const SourceBuffer &buffer;
  const char32_t *begin;
  const char32_t *current;
  const char32_t *end;

  size_t line = 1;
  size_t column = 1;

  std::vector<State> checkpoints;

  State current_state;

public:
  explicit TextStream(const SourceBuffer &buf)
      : buffer(buf), begin(buf.begin()), current(buf.begin()), end(buf.end()) {}

  bool eof() const { return current >= end; }
  char32_t peek(size_t offset = 0) const {
    const char32_t *p = current + offset;
    return p < end ? *p : U'\0';
  }

  const char32_t advance() {
    if (eof())
      return U'\0';
    char32_t c = *current++;
    if (c == U'\n') {
      line++;
      column = 1;
    } else {
      column++;
    }
    return c;
  }

  void advance_n(size_t n) {
    while (n--)
      advance();
  }

  Span span_from(const State &a, const State &b) const {
    return Span{a.ptr, b.ptr};
  }

  const char32_t *mark() const { return current; }

  State get_state() const {
    return {current, static_cast<size_t>(current - begin), line, column};
  }

  void rollback(const State &s) {
    current = s.ptr;
    line = s.line;
    column = s.column;
  }

  SourceRange range_from(const State &a, const State &b) const {
    return SourceRange{
        .begin =
            {
                .offset = static_cast<size_t>(a.ptr - buffer.begin()),
                .line = a.line,
                .column = a.column,
            },
        .end = {
            .offset = static_cast<size_t>(b.ptr - buffer.begin()),
            .line = b.line,
            .column = b.column,
        }};
  }

  void push_checkpoint() { checkpoints.push_back(get_state()); }
  void rollback_checkpoint() {
    if (!checkpoints.empty()) {
      rollback(checkpoints.back());
      checkpoints.pop_back();
    }
  }
  void discard_checkpoint() {
    if (!checkpoints.empty())
      checkpoints.pop_back();
  }

  template <typename Predicate> size_t advance_while(Predicate pred) {
    size_t count = 0;
    while (!eof() && pred(peek())) {
      advance();
      count++;
    }
    return count;
  }
};

} // namespace core::source
