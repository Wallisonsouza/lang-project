#pragma once
#include "core/source/SourceBuffer.hpp"

#include "core/token/Location.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "utils/Utf8.hpp"
#include <iostream>
#include <sstream>
#include <string>

namespace diagnostic {
struct VisualLine {
  std::string text;
  size_t caret_column;
};

static VisualLine make_visual_line(const std::string &line, size_t logical_column, size_t max_width = 120) {
  const size_t len = line.size();

  // coluna é 1-based
  size_t caret_index = (logical_column > 0) ? logical_column - 1 : 0;
  if (caret_index > len) caret_index = len;

  // // === MODO: erro começa aqui (strings, comentários, etc) ===
  // if (style == DiagnosticStyle::FromBegin) {
  //   size_t start = caret_index;
  //   size_t end = std::min(start + max_width, len);

  //   std::string text = line.substr(start, end - start);
  //   if (end < len) text += "...";

  //   return {text, 1};
  // }

  // === MODO: erro pontual (centralizado) ===
  if (len <= max_width) { return {line, logical_column}; }

  size_t half = max_width / 2;
  size_t start = (caret_index > half) ? caret_index - half : 0;
  size_t end = std::min(start + max_width, len);

  bool left_cut = start > 0;
  bool right_cut = end < len;

  std::string result;
  if (left_cut) result += "...";
  result += line.substr(start, end - start);
  if (right_cut) result += "...";

  size_t caret_visual = caret_index - start + 1 + (left_cut ? 3 : 0);

  return {result, caret_visual};
}

inline void print_diagnostic(const std::string &message, const Slice &slice, const core::source::SourceBuffer &buffer) {

  debug::Console::log(debug::Color::Red, message);
  std::ostringstream out;

  out << message << "\n";

  const auto &begin = slice.range.begin;
  out << " --> line " << begin.line << ", column " << begin.column << "\n";

  auto raw_line = utils::Utf::utf32to8(buffer.get_line(begin.line));
  auto visual = make_visual_line(raw_line, begin.column, 100);

  out << "  |\n";
  out << begin.line << " | " << visual.text << "\n";
  out << "  | ";

  for (size_t i = 1; i < visual.caret_column; ++i) out << ' ';
  out << "^\n";

  if (slice.range.begin.line != slice.range.end.line) { out << "note: string literal spans multiple lines\n"; }

  std::cerr << out.str();
}

} // namespace diagnostic
