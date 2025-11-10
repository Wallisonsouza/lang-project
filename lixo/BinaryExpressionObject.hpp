// #include "core/Object.hpp"
// #include <memory>
// #include <string>

// struct BinaryExpressionObject : Object {
//   std::string op;
//   std::shared_ptr<Object> left;
//   std::shared_ptr<Object> right;

//   std::string typeName() const override { return "BinaryExpression"; }

//   std::string toString() const override { return "BinaryExpression(" + (left ? left->toString() : "null") + " " + op + " " + (right ? right->toString() : "null") + ")"; }
// };
