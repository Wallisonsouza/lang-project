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

inline Slice operator+(const Slice &a, const Slice &b) {
  Slice result;
  result.range.begin = a.range.begin;
  result.range.end = b.range.end;
  result.span.begin = a.span.begin;
  result.span.end = b.span.end;
  return result;
}