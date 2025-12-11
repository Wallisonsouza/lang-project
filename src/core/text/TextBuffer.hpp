#pragma once
#include "TextSpan.hpp"
#include "core/utils/Utf8.hpp"
#include <cstddef>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

class TextBuffer {

private:
  std::u32string unicode;

public:
  const std::string path;

  TextBuffer() = default;
  explicit TextBuffer(const std::string &filepath) : path(filepath) { load_from_file(filepath); }

  void load_from_file(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Erro ao abrir arquivo: " + filepath);

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string utf8 = ss.str();

    if (!interpreter::utils::Utf8::utf8_to_utf32(utf8, unicode)) throw std::runtime_error("UTF-8 inválido no arquivo: " + filepath);
  }

  std::string u32_to_u8(const TextSpan &span) const {
    if (span.start > span.end || span.end > unicode.size()) return {};

    std::string out;
    out.reserve(span.length() * 4);
    for (size_t i = span.start; i < span.end; ++i) interpreter::utils::Utf8::encode(unicode[i], out);
    return out;
  }

  const std::u32string &u32() const { return unicode; }

  size_t u32_size() const { return unicode.size(); }

  // size_t hash_span(const TextSpan &span) const noexcept {
  //   size_t h = 0xcbf29ce484222325; // FNV-1a
  //   for (size_t i = span.start; i < span.end; ++i) h ^= static_cast<size_t>(unicode[i]), h *= 0x100000001b3;
  //   return h;
  // }

  // bool equal_span(const TextSpan &a, const TextSpan &b) const noexcept {
  //   if (a.length() != b.length()) return false;
  //   for (size_t i = 0; i < a.length(); ++i)
  //     if (unicode[a.start + i] != unicode[b.start + i]) return false;
  //   return true;
};
