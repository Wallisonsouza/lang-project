#pragma once
#include "argon/nodes/IntLiteralNode.hpp"
#include "core/ast.hpp"

struct StringLiteralNode : public Node {
  std::string value;
  explicit StringLiteralNode(std::string v) : value(std::move(v)) {}

  LanguagePrimitives execute(Environment &) override { return value; }

  std::string toString() const override {
    if (LangDebug::enableNodeDebug) {
      return "StringLiteral(\"" + value + "\")";
    } else {
      return "\"" + value + "\"";
    }
  }
};