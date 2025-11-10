// #pragma once

// #include "argon/argon_descriptor.hpp"
// #include "core/TokenUtils.hpp"
// #include "core/plugins/Solver.hpp"
// #include <memory>
// #include <string>

// class FloatSolver : public Solver {
// public:
//   std::shared_ptr<Object> solve(const std::shared_ptr<SolverContext> context) override {
//     auto token = TokenUtils::expectToken(context->tokens, TokenId::FLOAT_LITERAL);
//     if (!token) {
//       return nullptr;
//     }

//     float value;
//     try {
//       value = std::stof(token->lexeme);
//     } catch (...) {
//       return nullptr;
//     }

//     auto floatNode = std::make_shared<FloatObject>(value);
//     context->tokens->advance();
//     return floatNode;
//   }
// };
