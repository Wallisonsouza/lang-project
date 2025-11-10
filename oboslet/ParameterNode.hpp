// #pragma once
// #include "core/ast.hpp"

// struct ParameterNode : public Node {
//   std::string name;
//   std::unique_ptr<Node> defaultValue;

//   ParameterNode(std::string n, std::unique_ptr<Node> def = nullptr) : name(std::move(n)), defaultValue(std::move(def)) {}

//   std::string toString() const override {
//     if (defaultValue)
//       return name + " = " + defaultValue->toString();
//     return name;
//   }
//   LanguagePrimitives execute(Environment &) override { return {}; }
// };