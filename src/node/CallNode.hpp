#pragma once
#include "Ast.hpp"
#include "node/NativeFunctionNode.hpp"
#include "node/Nodes.hpp"

struct CallNode : public ASTNode {
  std::string funcName;
  std::vector<std::unique_ptr<ASTNode>> args;

  CallNode(std::string name, std::vector<std::unique_ptr<ASTNode>> arguments)
      : funcName(std::move(name)), args(std::move(arguments)) {}

  std::string toString() const override {
    std::string res = "CallNode { " + funcName + "(";
    for (size_t i = 0; i < args.size(); ++i) {
      res += args[i]->toString();
      if (i + 1 < args.size())
        res += ", ";
    }
    res += ") }";
    return res;
  }

  LanguagePrimitives execute(Environment &env) override {

    std::vector<LanguagePrimitives> argValues;

    for (std::unique_ptr<ASTNode> &arg : args) {
      argValues.push_back(arg->execute(env));
    }

    std::shared_ptr<ASTNode> node = env.getSymbol(funcName);

    // Se for uma função nativa
    if (auto nativeFunc = dynamic_cast<NativeFunctionNode *>(node.get())) {
      return nativeFunc->call(argValues);
    }

    /*    // Se for uma função do script
       if (auto scriptFunc = dynamic_cast<FunctionNode *>(node.get())) {
         // Cria um escopo local baseado na closure
         env.pushScope();
         auto localScope = env.currentScope();
         // Aqui você pode copiar variáveis da closure para o escopo local
         for (const auto &var : scriptFunc->closure->entries) {
           localScope->setSymbol(var.first, var.second);
         }

         // Define parâmetros
         for (size_t i = 0; i < scriptFunc->parameters.size(); ++i) {
           if (i < argValues.size()) {
             localScope->setSymbol(scriptFunc->parameters[i]->name,
                                   std::make_shared<LiteralNode>(argValues[i]));
           } else if (scriptFunc->parameters[i]->defaultValue) {
             localScope->setSymbol(scriptFunc->parameters[i]->name,
                                   scriptFunc->parameters[i]->defaultValue);
           } else {
             localScope->setSymbol(scriptFunc->parameters[i]->name,
                                   nullptr); // ou um valor default
           }
         }

         // Executa o corpo da função
         LanguagePrimitives result;
         for (auto &stmt : scriptFunc->body) {
           result = stmt->execute(env);
         }

         env.popScope();
         return result;
       } */

    throw std::runtime_error("Symbol is not a callable function: " + funcName);
  }
};