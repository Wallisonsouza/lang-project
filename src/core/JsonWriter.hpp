#include <ostream>
#include <string_view>
#include <vector>

struct JsonWriter {
  std::ostream &out;
  std::vector<bool> first; // controla vírgulas

  explicit JsonWriter(std::ostream &o) : out(o) {}

  // --- helpers ---
  void comma() {
    if (!first.empty()) {
      if (!first.back()) out << ",";
      first.back() = false;
    }
  }

  static void escape(std::ostream &o, std::string_view s) {
    for (char c : s) {
      switch (c) {
      case '"': o << "\\\""; break;
      case '\\': o << "\\\\"; break;
      case '\n': o << "\\n"; break;
      case '\r': o << "\\r"; break;
      case '\t': o << "\\t"; break;
      default: o << c;
      }
    }
  }

  void begin_object() {
    comma();
    out << "{";
    first.push_back(true);
  }

  void end_object() {
    out << "}";
    first.pop_back();
  }

  void begin_array() {
    comma();
    out << "[";
    first.push_back(true);
  }

  void end_array() {
    out << "]";
    first.pop_back();
  }

  void key(std::string_view k) {
    comma();
    out << "\"";
    escape(out, k);
    out << "\":";
    first.back() = true;
  }

  void string(std::string_view v) {
    comma();
    out << "\"";
    escape(out, v);
    out << "\"";
  }

  void number(int v) {
    comma();
    out << v;
  }

  void boolean(bool v) {
    comma();
    out << (v ? "true" : "false");
  }

  void null() {
    comma();
    out << "null";
  }
};
