/* #include "node/Nodes.hpp"
#include <memory>
#include <string>
#include <vector>

struct FunctionNode : public ASTNode {
  std::string name;
  std::vector<std::unique_ptr<ParameterNode>> parameters;
  std::vector<std::unique_ptr<ASTNode>> body;
  std::shared_ptr<Scope> closure;

  FunctionNode(std::string n,
               std::vector<std::unique_ptr<ParameterNode>> params,
               std::vector<std::unique_ptr<ASTNode>> b,
               std::shared_ptr<Scope> c)
      : name(std::move(n)), parameters(std::move(params)), body(std::move(b)),
        closure(std::move(c)) {}

  std::string toString() const override {
    std::string res = "Function " + name + "(";
    for (size_t i = 0; i < parameters.size(); ++i) {
      res += parameters[i]->toString();
      if (i + 1 < parameters.size())
        res += ", ";
    }
    res += ") { ... }";
    return res;
  }

  Value execute(Environment &env) override {
    // Cria um novo escopo para a execução da função
    auto localScope = std::make_shared<Scope>();
    // Copia a closure (variáveis externas)
    for (const auto &var : closure->variables) {
      localScope->setVar(var.first, var.second);
    }

    env.pushScope();
    env.currentScope() = localScope;

    Value result;
    for (auto &stmt : body) {
      result = stmt->execute(env);
    }

    env.popScope();
    return result;
  }
};
 */