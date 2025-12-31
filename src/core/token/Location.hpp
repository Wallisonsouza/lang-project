#pragma once

#include "core/source/Span.hpp"
#include <cstddef>

struct Location {
  size_t offset;
  size_t line;
  size_t column;
};

struct Range {
  Location begin;
  Location end;
};

struct Slice {
  Range range;
  core::source::Span span;
};
