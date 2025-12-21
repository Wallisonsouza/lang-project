#pragma once
#include "Utf8.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace utils {

class TextLoader {
public:
  static std::u32string load_file(const std::string &filepath) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) throw std::runtime_error("Erro ao abrir arquivo: " + filepath);

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string utf8 = ss.str();

    std::u32string out;
    if (!Utf::utf8_to_utf32(utf8, out)) throw std::runtime_error("UTF-8 inválido no arquivo: " + filepath);

    return out;
  }
};

} // namespace utils
