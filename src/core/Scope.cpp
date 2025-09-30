#include "Scope.hpp"
#include "ast.hpp"
#include "errors/ScopeErros.hpp"

void Scope::setSymbol(const std::string &name, std::shared_ptr<ASTNode> value) {
  if (hasSymbol(name)) {
    throw SymbolAlreadyExistsError(name);
  }

  entries[name] = std::move(value);
}

std::shared_ptr<ASTNode> Scope::getSymbol(const std::string &name) const {
  auto it = entries.find(name);
  if (it != entries.end()) {
    return it->second;
  }

  throw SymbolNotFoundError(name);
}

bool Scope::hasSymbol(const std::string &name) const { return entries.find(name) != entries.end(); }