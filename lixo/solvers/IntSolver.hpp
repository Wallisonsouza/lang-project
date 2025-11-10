// #pragma once
// #include "argon/argon_descriptor.hpp"
// #include "argon/objects/IntObject.hpp"
// #include "core/TokenUtils.hpp"
// #include "core/plugins/SolverPlugin.hpp"
// #include <memory>

// class IntSolver : public SolverPlugin {
// public:
//   std::shared_ptr<Object> solve(const std::shared_ptr<SolverContext> context) override {

//     auto token = TokenUtils::expectToken(context->tokens, TokenId::INT_LITERAL);
//     if (!token) {
//       return nullptr;
//     }

//     int value;
//     try {
//       value = std::stoi(token->lexeme);
//     } catch (...) {
//       return nullptr;
//     }

//     auto intNode = std::make_shared<IntObject>(value);
//     context->tokens->advance();
//     return intNode;
//   }
// };
