#pragma once
#include <chrono>
#include <iostream>
#include <unordered_map>

namespace debug {

enum class ColorCode {
  Reset,
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
  BrightBlack,
  BrightRed,
  BrightGreen,
  BrightYellow,
  BrightBlue,
  BrightMagenta,
  BrightCyan,
  BrightWhite
};

inline const char *toAnsi(ColorCode c) {
  switch (c) {
  case ColorCode::Reset:
    return "\033[0m";
  case ColorCode::Black:
    return "\033[30m";
  case ColorCode::Red:
    return "\033[31m";
  case ColorCode::Green:
    return "\033[32m";
  case ColorCode::Yellow:
    return "\033[33m";
  case ColorCode::Blue:
    return "\033[34m";
  case ColorCode::Magenta:
    return "\033[35m";
  case ColorCode::Cyan:
    return "\033[36m";
  case ColorCode::White:
    return "\033[37m";
  case ColorCode::BrightBlack:
    return "\033[90m";
  case ColorCode::BrightRed:
    return "\033[91m";
  case ColorCode::BrightGreen:
    return "\033[92m";
  case ColorCode::BrightYellow:
    return "\033[93m";
  case ColorCode::BrightBlue:
    return "\033[94m";
  case ColorCode::BrightMagenta:
    return "\033[95m";
  case ColorCode::BrightCyan:
    return "\033[96m";
  case ColorCode::BrightWhite:
    return "\033[97m";
  }
  return "\033[0m";
}

// ----------------------------------------
// StyledStream
// ----------------------------------------
class StyledStream {
  std::ostream &os;
  // se true, cada mudança de cor é automaticamente resetada no fim da próxima
  // operação de texto. por padrão false — preferível, mais previsível.
  bool autoReset;
  bool colorActive =
      false; // indica se uma cor foi definida e ainda não foi resetada

public:
  explicit StyledStream(std::ostream &out, bool autoReset_ = false)
      : os(out), autoReset(autoReset_) {}

  // Tratamento de ColorCode: não faz reset automático aqui
  StyledStream &operator<<(ColorCode color) {
    os << toAnsi(color);
    colorActive = (color != ColorCode::Reset);
    return *this;
  }

  // Qualquer outro tipo — NÃO emite Reset automaticamente.
  template <typename T> StyledStream &operator<<(const T &value) {
    os << value;
    // Se você quer comportamento autoReset, pode resetar aqui
    if (autoReset && colorActive) {
      os << toAnsi(ColorCode::Reset);
      colorActive = false;
    }
    return *this;
  }

  // manipuladores padrão
  StyledStream &operator<<(std::ostream &(*manip)(std::ostream &)) {
    os << manip;
    // se for endl e autoReset estiver ligado, resetamos também
    if (manip == static_cast<std::ostream &(*)(std::ostream &)>(std::endl) &&
        autoReset && colorActive) {
      os << toAnsi(ColorCode::Reset);
      colorActive = false;
    }
    return *this;
  }

  std::ostream &getStream() { return os; }

  // Métodos utilitários se quiser controlar explicitamente
  void resetColor() {
    if (colorActive) {
      os << toAnsi(ColorCode::Reset);
      colorActive = false;
    }
  }
};

// ----------------------------------------
// Console
// ----------------------------------------

class Console {
private:
  using Clock = std::chrono::high_resolution_clock;
  inline static std::unordered_map<std::string, Clock::time_point> timers;

public:
  static void time(const std::string &label) {
    timers[label] = Clock::now();
    debug(ColorCode::BrightBlack, "[TIME START] ", label);
  }

  static void timeEnd(const std::string &label) {
    auto it = timers.find(label);
    if (it == timers.end()) {
      warn(ColorCode::Yellow, "[WARN] timeEnd chamado sem time(): ", label);
      return;
    }

    auto end = Clock::now();
    auto elapsed_ns =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end - it->second)
            .count();
    timers.erase(it);

    double seconds = elapsed_ns / 1e9;
    double millis = elapsed_ns / 1e6;
    double micros = elapsed_ns / 1e3;

    std::string formatted;

    if (seconds >= 1.0) {
      formatted = std::to_string(seconds) + "s";
    } else if (millis >= 1.0) {
      formatted = std::to_string(millis) + "ms";
    } else {
      formatted = std::to_string(micros) + "µs";
    }

    debug(ColorCode::BrightCyan, "[TIME END] ", label, " -> ", formatted);
  }

  template <typename... Args> static void log(const Args &...args) {
    StyledStream ss(std::cout);
    (ss << ... << args);
    ss << std::endl;
  }

  template <typename... Args> static void warn(const Args &...args) {
    StyledStream ss(std::cerr);
    ss << ColorCode::Yellow;
    (ss << ... << args);
    ss << std::endl;
  }

  template <typename... Args> static void error(const Args &...args) {
    StyledStream ss(std::cerr);
    ss << ColorCode::BrightRed;
    (ss << ... << args);
    ss << std::endl;
  }

  template <typename... Args> static void debug(const Args &...args) {
    StyledStream ss(std::cout);
    ss << ColorCode::Cyan;
    (ss << ... << args);
    ss << std::endl;
  }
};
} // namespace debug
