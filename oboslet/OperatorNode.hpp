    // #pragma once
    // #include "core/ast.hpp"
    // #include <string>

    // enum class OperatorKind {
    //   Add,
    //   Subtract,
    //   Multiply,
    //   Divide,
    // };

    // struct OperatorNode : public Node<OperatorKind> {
    //   explicit OperatorNode(OperatorKind k){value = k; }

    //   OperatorKind execute(Environment &) override { return value; }

    //   std::string toString() const override {
    //     switch (value) {
    //     case OperatorKind::Add:
    //       return "+";
    //     case OperatorKind::Subtract:
    //       return "-";
    //     case OperatorKind::Multiply:
    //       return "*";
    //     case OperatorKind::Divide:
    //       return "/";
    //     default:
    //       return "?";
    //     }
    //   }
    // };