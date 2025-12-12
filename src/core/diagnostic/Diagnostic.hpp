#pragma once
#include "Category.hpp"
#include "Severity.hpp"
#include <string>

namespace core::diagnostics {

struct Diagnostic {

  std::string message;
  std::string file;
  int line;
  int column;
  Severity severity;
  Category category;

  Diagnostic(const std::string &msg, const std::string &f, int l, int c,
             Severity s = Severity::Error, Category cat = Category::Parser)
      : message(msg), file(f), line(l), column(c), severity(s), category(cat) {}
};

} // namespace core::diagnostics