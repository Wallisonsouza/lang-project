#pragma once

#include "Scope.hpp"
#include "errors/ScopeErros.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Environment {
private:
  std::vector<std::shared_ptr<Scope>> scopes;
  std::unordered_map<std::string, std::shared_ptr<ASTNode>> imports;

public:
  std::unordered_map<std::string, std::shared_ptr<ASTNode>> exports;

  Environment() { pushScope(); }

  void pushScope() { scopes.push_back(std::make_shared<Scope>()); }

  void popScope() {
    if (scopes.empty())
      throw ScopeError("No scope available to pop");
    scopes.pop_back();
  }

  std::shared_ptr<Scope> currentScope() {
    if (scopes.empty())
      throw ScopeError("No current scope available");
    return scopes.back();
  }

  void setSymbol(const std::string &name, std::shared_ptr<ASTNode> node) {
    currentScope()->setSymbol(name, std::move(node));
  }

  bool hasSymbol(const std::string &name) const {
    if (imports.find(name) != imports.end())
      return true;

    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      if ((*it)->hasSymbol(name))
        return true;
    }
    return false;
  }

  std::shared_ptr<ASTNode> getSymbol(const std::string &name) {
    auto it_import = imports.find(name);
    if (it_import != imports.end())
      return it_import->second;

    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
      if ((*it)->hasSymbol(name))
        return (*it)->getSymbol(name);
    }

    throw SymbolNotFoundError(name);
  }

  void exportSymbol(const std::string &name, std::shared_ptr<ASTNode> node) {
    exports[name] = std::move(node);
  }

  void importAll(Environment &env) {
    for (auto &pair : env.exports) {
      imports[pair.first] = pair.second;
    }
  }
};
