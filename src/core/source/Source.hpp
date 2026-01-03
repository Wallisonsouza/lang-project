#pragma once

#include "SourceBuffer.hpp"
#include "utils/TextLoader.hpp"
#include <string>
#include <utility>

namespace core::source {

struct Source {
  std::string path;
  SourceBuffer buffer;

  Source(std::string p) : path(std::move(p)), buffer(utils::TextLoader::load_file(path)) {}
};

} // namespace core::source
