#pragma once
#include "core/text/SourceBuffer.hpp"
#include <string>

namespace core::source {

struct Source {
  std::string path;
  SourceBuffer buffer;

  // Construtor
  Source(std::string p, std::u32string_view src) : path(std::move(p)), buffer(src) {}
};

} // namespace core::source
