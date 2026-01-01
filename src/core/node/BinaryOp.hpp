#pragma once
#include <string>

namespace core::node {
enum class BinaryOperation {
  Add,
  Subtract,
  Multiply,
  Divide,
  Modulo,

};

inline std::string binary_op_to_string(BinaryOperation op) {
  switch (op) {
  case BinaryOperation::Add: return "+";
  case BinaryOperation::Subtract: return "-";
  case BinaryOperation::Multiply: return "*";
  case BinaryOperation::Divide: return "/";
  case BinaryOperation::Modulo: return "%";
  default: return "?";
  }
}
} // namespace core::node
