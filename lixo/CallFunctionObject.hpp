// #pragma once
// #include "core/Object.hpp"
// #include <memory>
// #include <string>
// #include <vector>
// #include <sstream>

// struct CallFunctionObject: Object {
//     std::string name;
//     std::vector<std::shared_ptr<Object>> args;

//     std::string typeName() const override { 
//         return "CallFunction"; 
//     }

//     std::string toString() const override {
//         std::ostringstream oss;
//         oss << name << "(";
//         for (size_t i = 0; i < args.size(); i++) {
//             if (args[i]) {
//                 oss << args[i]->toString();
//             } else {
//                 oss << "null";
//             }
//             if (i + 1 < args.size()) oss << ", ";
//         }
//         oss << ")";
//         return oss.str();
//     }
// };
