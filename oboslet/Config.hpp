// #pragma once
// #include <algorithm>
// #include <fstream>
// #include <stdexcept>
// #include <string>

// struct Config {
//   std::string sourcePath = "./";
//   std::string extension  = ".orb";
//   bool debug             = false;

//   static std::string trim(const std::string &str) {
//     auto start = str.find_first_not_of(" \t\n\r");
//     auto end   = str.find_last_not_of(" \t\n\r");
//     return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
//   }

//   static Config load(const std::string &filename) {
//     Config cfg;
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//       throw std::runtime_error("Erro ao abrir config: " + filename);
//     }

//     std::string line;
//     while (std::getline(file, line)) {
//       line = trim(line);
//       if (line.empty() || line[0] == '/' || line[0] == '{' || line[0] == '}')
//         continue;

//       if (line.find("\"source_path\"") != std::string::npos) {
//         auto start = line.find(":");
//         auto value = trim(line.substr(start + 1));
//         value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
//         value.erase(std::remove(value.begin(), value.end(), ','), value.end());
//         cfg.sourcePath = value;
//       } else if (line.find("\"extension\"") != std::string::npos) {
//         auto start = line.find(":");
//         auto value = trim(line.substr(start + 1));
//         value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
//         value.erase(std::remove(value.begin(), value.end(), ','), value.end());
//         cfg.extension = value;
//       } else if (line.find("\"debug\"") != std::string::npos) {
//         cfg.debug = (line.find("true") != std::string::npos);
//       }
//     }

//     return cfg;
//   }
// };