// #pragma once
// #include "core/Object.hpp"
// #include <memory>
// #include <string>

// struct AssignmentObject : Object {
//     std::string name;
//     std::shared_ptr<Object> value;

//     std::string typeName() const override { return "Assignment"; }

//     std::string toString() const override {
//         return name + " = " + (value ? value->toString() : "null");
//     }
// };