#pragma once
#include <cstddef>
#include <string>
#include <string_view>

namespace core::text {

class TextBuffer {
private:
  std::u32string unicode;

public:
  explicit TextBuffer(std::u32string_view data) : unicode(data) {}

  const std::u32string &u32() const { return unicode; }
  size_t u32_size() const { return unicode.size(); }
};

} // namespace core::text
