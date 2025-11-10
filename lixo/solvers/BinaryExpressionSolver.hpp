// #pragma once
// #include "argon/objects/BinaryExpressionObject.hpp"
// #include "core/Solver.hpp"
// #include <memory>

// class BinaryExpressionSolver : public SolverPlugin {
// public:
//   std::shared_ptr<Object> solve(const std::shared_ptr<SolverContext> context) override {
//     auto &tokens = context->tokens;

//     if (!context || !context->tokens || !context->tokens->hasNext()) {
//       return nullptr;
//     }

//     auto token = context->tokens->current();
//     if (!token) {
//       context->tokens->advance();
//       return nullptr;
//     }

//     if (!tokens || !tokens->hasNext())
//       return nullptr;

//     // Salva posição inicial para rollback
//     tokens->saveState();

//     // Resolve o primeiro operando
//     auto left = Solver::NextExpression(context);
//     if (!left) {
//       tokens->rollback();
//       return nullptr;
//     }

//     // // Espera um operador
//     // auto opToken = tokens->current();
//     // if (!opToken || opToken->descriptor->type != TokenType::OPERATOR) {
//     //   tokens->rollback();
//     //   return nullptr;
//     // }
//     // std::string op = opToken->lexeme;
//     // tokens->advance();

//     // // Resolve o segundo operando
//     // auto right = Solver::NextExpression(context);
//     // if (!right) {
//     //   tokens->rollback();
//     //   return nullptr;
//     // }

//     // auto binExpr   = std::make_shared<BinaryExpressionObject>();
//     // binExpr->left  = left;
//     // binExpr->op    = opToken->lexeme;
//     // binExpr->right = right;

//     // return binExpr;
//   }
// };
