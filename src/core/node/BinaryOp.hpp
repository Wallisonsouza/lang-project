#pragma once
#include <string>

namespace core::node {
enum class BinaryOp {
  Add,
  Subtract,
  Multiply,
  Divide,
  Modulo,

};

inline std::string binary_op_to_string(BinaryOp op) {
  switch (op) {
  case BinaryOp::Add:
    return "+";
  case BinaryOp::Subtract:
    return "-";
  case BinaryOp::Multiply:
    return "*";
  case BinaryOp::Divide:
    return "/";
  case BinaryOp::Modulo:
    return "%";
  default:
    return "?";
  }
}
} // namespace core::node
