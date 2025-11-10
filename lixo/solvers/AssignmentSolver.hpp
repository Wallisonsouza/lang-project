// #pragma once
// #include "argon/argon_descriptor.hpp"
// #include "argon/objects/AssignmentObject.hpp"
// #include "core/Object.hpp"
// #include "core/Solver.hpp"
// #include "core/Token.hpp"
// #include "core/plugins/SolverPlugin.hpp"
// #include <memory>
// #include <string>

// class AssignmentSolver : public SolverPlugin {
// public:
//   bool canSolve(const Stream<Token> &tokens) override { return true; }

//   std::shared_ptr<Object> solve(Stream<Token> &stream, Context<SolverPlugin> &context) override {
//     if (!stream.hasNext())
//       return nullptr;

//     auto currentToken = stream.current();
//     if (currentToken->descriptor->id != TokenId::IDENTIFIER)
//       return nullptr;

//     std::string varName = currentToken->lexeme;
//     stream.advance();

//     // Verifica se o próximo token é '='
//     if (!stream.hasNext() || stream.current()->descriptor->id != TokenId::EQUAL) {
//       return nullptr;
//     }
//     stream.advance(); // pular '='

//     // Resolve o valor usando o solver principal (delegação)
//     auto valueNode = Solver::SolveExpression(stream, context);
//     if (!valueNode)
//       return nullptr;

//     // Cria o nó AssignmentObject
//     auto assignNode   = std::make_shared<AssignmentObject>();
//     assignNode->name  = varName;
//     assignNode->value = valueNode;

//     return assignNode;
//   }
// };
