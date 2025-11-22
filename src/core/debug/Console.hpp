#pragma once
#include <iostream>
#include <sstream>

namespace lang::debug {

class Console {
private:
  template <typename T> static void print_one(std::ostream &os, const T &value) { os << value; }

  template <typename T, typename... Rest> static void print_multi(std::ostream &os, const T &first, const Rest &...rest) {
    os << first;
    if constexpr (sizeof...(rest) > 0) {
      os << " ";
      print_multi(os, rest...);
    }
  }

public:
  template <typename... Args> static void log(const Args &...args) {
    std::ostringstream ss;
    ss << "[LOG]: ";
    print_multi(ss, args...);
    std::cout << ss.str() << std::endl;
  }

  template <typename... Args> static void warn(const Args &...args) {
    std::ostringstream ss;
    ss << "\033[33m[WARNING]: ";
    print_multi(ss, args...);
    ss << "\033[0m";
    std::cerr << ss.str() << std::endl;
  }

  template <typename... Args> static void error(const Args &...args) {
    std::ostringstream ss;
    ss << "\033[31m[ERROR]: ";
    print_multi(ss, args...);
    ss << "\033[0m";
    std::cerr << ss.str() << std::endl;
  }

  template <typename... Args> static void debug(const Args &...args) {
    std::ostringstream ss;
    ss << "\033[36m[DEBUG]: ";
    print_multi(ss, args...);
    ss << "\033[0m";
    std::cout << ss.str() << std::endl;
  }
};

} // namespace lang::debug
