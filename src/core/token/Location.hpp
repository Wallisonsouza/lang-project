#pragma once
#include <cstddef>

struct SourceLocation {
  size_t offset;
  size_t line;
  size_t column;
};

struct SourceRange {
  SourceLocation begin;
  SourceLocation end;
};
