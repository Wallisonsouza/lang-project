// #pragma once

// #include "argon/argon_descriptor.hpp"
// #include "argon/objects/StringObject.hpp"
// #include "core/TokenUtils.hpp"
// #include "core/plugins/SolverPlugin.hpp"
// #include <memory>

// class StringSolver : public SolverPlugin {
// public:
//   std::shared_ptr<Object> solve(const std::shared_ptr<SolverContext> context) override {
//     auto token = TokenUtils::expectToken(context->tokens, TokenId::STRING_LITERAL);

//     if (!token) {
//       return nullptr;
//     }

//     auto stringNode = std::make_shared<StringObject>(token->lexeme);
//     context->tokens->advance();
//     return stringNode;
//   }
// };
