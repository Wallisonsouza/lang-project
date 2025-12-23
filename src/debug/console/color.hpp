#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

namespace debug {

class Color {
public:
  uint8_t r, g, b, a;

  Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
      : r(red), g(green), b(blue), a(alpha) {}

  std::string fg() const {
    std::ostringstream oss;
    oss << "\033[38;2;" << int(r) << ";" << int(g) << ";" << int(b) << "m";
    return oss.str();
  }

  std::string bg() const {
    std::ostringstream oss;
    oss << "\033[48;2;" << int(r) << ";" << int(g) << ";" << int(b) << "m";
    return oss.str();
  }

  static std::string reset() { return "\033[0m"; }

  static const Color Black;
  static const Color Red;
  static const Color Green;
  static const Color Yellow;
  static const Color Blue;
  static const Color Magenta;
  static const Color Cyan;
  static const Color White;

  static const Color BrightBlack;
  static const Color BrightRed;
  static const Color BrightGreen;
  static const Color BrightYellow;
  static const Color BrightBlue;
  static const Color BrightMagenta;
  static const Color BrightCyan;
  static const Color BrightWhite;

  static const Color Orange;
  static const Color Purple;
  static const Color Pink;
  static const Color Teal;
  static const Color Lime;
  static const Color Navy;
  static const Color Maroon;
  static const Color Olive;
};

inline const Color Color::Black(0, 0, 0);
inline const Color Color::Red(255, 0, 0);
inline const Color Color::Green(0, 255, 0);
inline const Color Color::Yellow(255, 255, 0);
inline const Color Color::Blue(0, 0, 255);
inline const Color Color::Magenta(255, 0, 255);
inline const Color Color::Cyan(0, 255, 255);
inline const Color Color::White(255, 255, 255);

inline const Color Color::BrightBlack(128, 128, 128);
inline const Color Color::BrightRed(255, 128, 128);
inline const Color Color::BrightGreen(128, 255, 128);
inline const Color Color::BrightYellow(255, 255, 128);
inline const Color Color::BrightBlue(128, 128, 255);
inline const Color Color::BrightMagenta(255, 128, 255);
inline const Color Color::BrightCyan(128, 255, 255);
inline const Color Color::BrightWhite(255, 255, 255);

inline const Color Color::Orange(255, 165, 0);
inline const Color Color::Purple(128, 0, 128);
inline const Color Color::Pink(255, 192, 203);
inline const Color Color::Teal(0, 128, 128);
inline const Color Color::Lime(0, 255, 0);
inline const Color Color::Navy(0, 0, 128);
inline const Color Color::Maroon(128, 0, 0);
inline const Color Color::Olive(128, 128, 0);

} // namespace debug