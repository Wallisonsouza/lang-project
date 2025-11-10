// #pragma once
// #include "argon/argon_descriptor.hpp"
// #include "argon/objects/CallFunctionObject.hpp"
// #include "core/Solver.hpp"
// #include "core/Token.hpp"
// #include "core/plugins/SolverPlugin.hpp"
// #include <string>

// class FunctionCallSolver : public SolverPlugin {
// public:
//   bool canSolve(const Stream<Token> &tokens) override {
//     auto current = tokens.peek(0);
//     return current && current->descriptor->type == TokenType::IDENTIFIER;
//   }

//   std::shared_ptr<Object> solve(Stream<Token> &stream, Context<SolverPlugin> &context) override {
//     auto currentToken = stream.peek(0);
//     if (!currentToken)
//       return nullptr;

//     std::string functionName = currentToken->lexeme;
//     stream.advance();

//     auto openParen = stream.peek(0);
//     if (!openParen || openParen->descriptor->id != TokenId::OPEN_PAREN)
//       return nullptr;
//     stream.advance(); // pular '('

//     std::vector<std::shared_ptr<Object>> params;

//     while (stream.hasNext()) {
//       auto t = stream.peek(0);
//       if (!t)
//         break;

//       if (t->descriptor->id == TokenId::CLOSE_PAREN) {
//         stream.advance(); // pular ')'
//         break;
//       }

//       if (t->descriptor->id == TokenId::COMMA) {
//         stream.advance(); // pular ','
//         continue;
//       }

//       auto paramNode = Solver::SolveExpression(stream, context);

//       if (paramNode) {
//         params.push_back(paramNode);
//       }

//       else
//         break; // evita loop infinito caso SolveExpression falhe
//     }

//     // Criar o nó CallExpression
//     auto callNode  = std::make_shared<CallFunctionObject>();
//     callNode->name = functionName;
//     callNode->args = params;

//     return callNode;
//   }
// };
