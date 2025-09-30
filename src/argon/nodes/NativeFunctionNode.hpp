#include "core/ast.hpp"
#include <functional>
#include <vector>

struct NativeFunctionNode : public ASTNode {
  // assinatura das funções nativas:
  std::function<LanguagePrimitives(const std::vector<LanguagePrimitives> &)> impl;

  explicit NativeFunctionNode(std::function<LanguagePrimitives(const std::vector<LanguagePrimitives> &)> f) : impl(std::move(f)) {}

  LanguagePrimitives execute(Environment &) override {
    // Executar sem argumentos não faz sentido -> lança exceção
    throw std::runtime_error("Native function called without arguments.");
  }

  // usado por CallNode para realmente chamar
  LanguagePrimitives call(const std::vector<LanguagePrimitives> &args) { return impl(args); }

  std::string toString() const override { return "<native function>"; }
};
