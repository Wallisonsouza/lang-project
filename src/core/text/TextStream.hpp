#pragma once
#include "TextBuffer.hpp"
#include "TextSpan.hpp"
#include <cstddef>
#include <vector>

namespace core::text {
class TextStream {
public:
  struct State {
    const char32_t *ptr;
    size_t line;
    size_t column;
  };

private:
  const core::text::TextBuffer &buffer;
  const char32_t *begin;
  const char32_t *current;
  const char32_t *end;

  size_t line = 1;
  size_t column = 1;

  std::vector<State> checkpoints;

public:
  explicit TextStream(const core::text::TextBuffer &buf)
      : buffer(buf), begin(buf.u32().data()), current(buf.u32().data()),
        end(buf.u32().data() + buf.u32_size()) {}

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

  const char32_t *mark() const { return current; }

  TextSpan span_from(const char32_t *start) const {
    size_t start_pos = start - begin;
    size_t len = current - start;
    return TextSpan{start_pos, start_pos + len, line, column - len};
  }

  size_t current_pos() const { return current - begin; }
  size_t current_line() const { return line; }
  size_t current_column() const { return column; }

  State get_state() const { return {current, line, column}; }

  void rollback(const State &state) {
    current = state.ptr;
    line = state.line;
    column = state.column;
  }

  TextSpan span_from(const State &start, const State &end) const {
    return TextSpan{
        static_cast<size_t>(start.ptr - buffer.u32().data()), // start offset
        static_cast<size_t>(end.ptr - buffer.u32().data()),   // end offset
        start.line,                                           // linha inicial
        start.column,                                         // coluna inicial
        end.column                                            // coluna final
    };
  }

  void push_checkpoint() { checkpoints.push_back(get_state()); }

  void rollback_checkpoint() {
    if (checkpoints.empty())
      return;
    rollback(checkpoints.back());
    checkpoints.pop_back();
  }

  void discard_checkpoint() {
    if (!checkpoints.empty())
      checkpoints.pop_back();
  }
};
} // namespace core::text
