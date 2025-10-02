#pragma once
#include "core/ast.hpp"

class LangDebug {
public:
  static inline bool enableNodeDebug = true;
};

struct IntLiteralNode : public Node {
  int value;
  explicit IntLiteralNode(int v) : value(v) {}

  LanguagePrimitives execute(Environment &) override { return value; }

  std::string toString() const override {
    if (LangDebug::enableNodeDebug) {
      return "IntLiteral(" + std::to_string(value) + ")";
    } else {
      return std::to_string(value);
    }
  }
};
