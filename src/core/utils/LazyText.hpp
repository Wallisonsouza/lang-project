#pragma once
#include "core/utils/Utf8.hpp"
#include <fstream>
#include <string>

namespace lang::utils {
class LazyText {

private:
  std::ifstream file_;
  std::u32string current_line_;
  std::u32string next_line_buffer_;
  bool eof_reached_     = false;
  bool has_next_buffer_ = false;
  size_t line_index_    = 0;

  void fillNextBuffer() {
    if (!has_next_buffer_ && !file_.eof()) {
      std::string line;
      if (std::getline(file_, line)) {
        next_line_buffer_ = lang::utils::Utf8Codec::decode(line);
        has_next_buffer_  = true;
      } else {
        eof_reached_ = true;
      }
    }
  }

public:
  explicit LazyText(const std::string &filepath) : file_(filepath) {
    if (!file_.is_open()) {
      throw std::runtime_error("LazyText: não foi possível abrir o arquivo '" + filepath + "'");
    }
    advance();
  }

  void advance() {
    if (has_next_buffer_) {
      current_line_    = std::move(next_line_buffer_);
      has_next_buffer_ = false;
    } else {
      std::string line;
      if (std::getline(file_, line)) {
        current_line_ = lang::utils::Utf8Codec::decode(line);
      } else {
        eof_reached_ = true;
        current_line_.clear();
        return;
      }
    }
    ++line_index_;
    fillNextBuffer();
  }

  [[nodiscard]] std::u32string &getLine() { return current_line_; }

  [[nodiscard]] std::u32string peek() {
    fillNextBuffer();
    return has_next_buffer_ ? next_line_buffer_ : std::u32string{};
  }

  [[nodiscard]] bool isEOF() const { return eof_reached_; }

  [[nodiscard]] std::u32string combine(size_t startIndex) {
    fillNextBuffer();
    if (!has_next_buffer_)
      return current_line_;

    if (startIndex >= current_line_.size())
      startIndex = current_line_.size();

    std::u32string result(current_line_.begin() + startIndex, current_line_.end());
    result.insert(result.end(), next_line_buffer_.begin(), next_line_buffer_.end());
    return result;
  }

  [[nodiscard]] size_t getLineIndex() const { return line_index_; }
};
} // namespace lang::utils
