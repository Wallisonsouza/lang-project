#pragma once
#include "core/text/TextSpan.hpp"
#include <cassert>
#include <string>
#include <string_view>
#include <vector>

namespace core::source {

class SourceBuffer {
  std::u32string data;
  std::vector<std::u32string_view> lines;

public:
  explicit SourceBuffer(std::u32string_view src) : data(src) {
    size_t start = 0;
    while (start < data.size()) {
      size_t end = data.find(U'\n', start);
      if (end == std::u32string::npos) end = data.size();
      lines.push_back(std::u32string_view(data.data() + start, end - start));
      start = end + 1;
    }
  }

  const char32_t *begin() const { return data.data(); }
  const char32_t *end() const { return data.data() + data.size(); }
  size_t size() const { return data.size(); }
  std::u32string_view view() const { return {data.data(), data.size()}; }

  std::u32string get_text(const Span &span) const {
    assert(span.begin >= data.data() && span.end <= data.data() + data.size());
    return std::u32string(span.begin, span.end);
  }

  // --- Novo: retorna a linha inteira pelo número (1-based) ---
  std::u32string_view get_line(size_t line_number) const {
    if (line_number == 0 || line_number > lines.size()) return {};
    return lines[line_number - 1];
  }

  // --- Novo: calcula linha e coluna a partir de um ponteiro ---
  std::pair<size_t, size_t> get_line_column(const char32_t *ptr) const {
    size_t line = 1;
    size_t column = 1;
    for (auto it = data.data(); it < ptr && it < data.data() + data.size(); ++it) {
      if (*it == U'\n') {
        line++;
        column = 1;
      } else {
        column++;
      }
    }
    return {line, column};
  }
};

} // namespace core::source
