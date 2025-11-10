#pragma once
#include "core/utils/Utf8.hpp"
#include <string>

namespace lang::utils {

class Utf32 {
public:
  [[nodiscard]] inline static std::u32string makeText(const std::string &s) { return utils::Utf8Codec::decode(s); }
};

struct Utf32Hash {
  size_t operator()(const std::u32string &v) const noexcept {
    size_t hash = 0;
    std::hash<uint32_t> hasher;
    for (uint32_t cp : v) {
      hash ^= hasher(cp) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
    }
    return hash;
  }
};

} // namespace lang::utils