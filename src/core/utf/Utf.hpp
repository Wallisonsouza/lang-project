#include <cstdint>
#include <string>
#include <vector>

namespace interpreter::core {

class UTF {
  using utf_32_char = char32_t;
  using utf_32_string = std::vector<utf_32_char>;

public:
  static utf_32_string make_utf32_string(const char32_t *str, size_t length) { return utf_32_string(str, str + length); }

  static utf_32_string convert_utf8_to_utf32(const std::string &utf8_str) {
    utf_32_string result;
    size_t i = 0;

    while (i < utf8_str.size()) {
      uint8_t c = static_cast<uint8_t>(utf8_str[i]);
      uint32_t cp = 0;
      size_t nbytes = 0;

      if ((c & 0x80) == 0) {
        cp = c;
        nbytes = 1;
      } else if ((c & 0xE0) == 0xC0 && i + 1 < utf8_str.size()) {
        cp = ((c & 0x1F) << 6) | (utf8_str[i + 1] & 0x3F);
        nbytes = 2;
      } else if ((c & 0xF0) == 0xE0 && i + 2 < utf8_str.size()) {
        cp = ((c & 0x0F) << 12) | ((utf8_str[i + 1] & 0x3F) << 6) | (utf8_str[i + 2] & 0x3F);
        nbytes = 3;
      } else if ((c & 0xF8) == 0xF0 && i + 3 < utf8_str.size()) {
        cp = ((c & 0x07) << 18) | ((utf8_str[i + 1] & 0x3F) << 12) | ((utf8_str[i + 2] & 0x3F) << 6) | (utf8_str[i + 3] & 0x3F);
        nbytes = 4;
      } else {
        ++i;
        continue;
      }

      result.push_back(cp);
      i += nbytes;
    }

    return result;
  }
};

} // namespace interpreter::core
