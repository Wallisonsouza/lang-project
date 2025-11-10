  // #pragma once
  // #include "core/ast.hpp"
  // #include <memory>
  // #include <string>

  // enum class BinaryOp { Add, Subtract, Multiply, Divide };

  // struct BinaryExpression : public Node {
  //   std::shared_ptr<Node> left;
  //   std::shared_ptr<Node> right;
  //   BinaryOp op;

  //   BinaryExpression(std::shared_ptr<Node> lhs, std::shared_ptr<Node> rhs, BinaryOp oper) : left(lhs), right(rhs), op(oper) {}

  //   LanguagePrimitives execute(Environment &env) override {
  //     auto l = left->execute(env);
  //     auto r = right->execute(env);

  //     int lv = std::get<int>(l);
  //     int rv = std::get<int>(r);

  //     switch (op) {
  //     case BinaryOp::Add:
  //       return lv + rv;
  //     case BinaryOp::Subtract:
  //       return lv - rv;
  //     case BinaryOp::Multiply:
  //       return lv * rv;
  //     case BinaryOp::Divide:
  //       return lv / rv;
  //     }
  //     return 0;
  //   }

  //   std::string toString() const override {
  //     std::string oper;
  //     switch (op) {
  //     case BinaryOp::Add:
  //       oper = "+";
  //       break;
  //     case BinaryOp::Subtract:
  //       oper = "-";
  //       break;
  //     case BinaryOp::Multiply:
  //       oper = "*";
  //       break;
  //     case BinaryOp::Divide:
  //       oper = "/";
  //       break;
  //     }
  //     return "[BinaryExpression](" + left->toString() + " " + oper + " " + right->toString() + ")";
  //   }
  // };
