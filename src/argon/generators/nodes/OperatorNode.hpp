#pragma once
#include "core/ast.hpp"
#include <string>

enum class OperatorKind {
  Add,
  Subtract,
  Multiply,
  Divide,
};

struct OperatorNode : public Node {
  OperatorKind kind;
  explicit OperatorNode(OperatorKind k) : kind(k) {}

  LanguagePrimitives execute(Environment &) override { return toString(); }

  std::string toString() const override {
    switch (kind) {
    case OperatorKind::Add:
      return "+";
    case OperatorKind::Subtract:
      return "-";
    case OperatorKind::Multiply:
      return "*";
    case OperatorKind::Divide:
      return "/";
    default:
      return "?";
    }
  }
};