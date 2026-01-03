#pragma once
#include "Span.hpp"
#include <cassert>
#include <string>
#include <string_view>
#include <vector>

namespace core::source {

class SourceBuffer {
  std::string data;
  std::vector<std::string_view> lines;

public:
  explicit SourceBuffer(std::string_view src) : data(src) {
    size_t start = 0;
    while (start < data.size()) {
      size_t end = data.find('\n', start);
      if (end == std::string::npos) end = data.size();
      lines.push_back(std::string_view(data.data() + start, end - start));
      start = end + 1;
    }
  }

  const char *begin() const { return data.data(); }
  const char *end() const { return data.data() + data.size(); }
  size_t size() const { return data.size(); }
  std::string_view view() const { return {data.data(), data.size()}; }

  std::string_view get_line(size_t line_number) const {
    if (line_number == 0 || line_number > lines.size()) return {};
    return lines[line_number - 1];
  }

  std::string get_text(const Span &span) const {
    assert(span.begin >= data.data() && span.end <= data.data() + data.size());
    return std::string(span.begin, span.end);
  }

  const char *line_begin(size_t line_number) const {
    // linha 1 = índice 0
    if (line_number == 0 || line_number > lines.size()) return nullptr;
    return lines[line_number - 1].data();
  }

  size_t line_count() const { return lines.size(); }
};

} // namespace core::source
