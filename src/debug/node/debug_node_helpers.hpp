#pragma once
#include <string>

namespace debug::node {

inline std::string child_prefix(bool isLast) {
  return isLast ? "    " : "│   ";
}
inline std::string connector(bool isLast) { return isLast ? "└─ " : "├─ "; }

} // namespace debug::node
