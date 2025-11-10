// #pragma once
// #include "core/Object.hpp"
// #include "core/Scope.hpp"

// #include "errors/ScopeErros.hpp"
// #include <memory>
// #include <string>
// #include <unordered_map>
// #include <vector>

// class Environment {
// private:
//   std::vector<std::shared_ptr<Scope>> scopes;
//   std::unordered_map<std::string, std::shared_ptr<Object>> imports;

// public:
//   std::unordered_map<std::string, std::shared_ptr<Object>> exports;

//   Environment() { pushScope(); }

//   void pushScope() { scopes.push_back(std::make_shared<Scope>()); }

//   void popScope() {
//     if (scopes.empty())
//       throw ScopeError("No scope available to pop");
//     scopes.pop_back();
//   }

//   std::shared_ptr<Scope> currentScope() {
//     if (scopes.empty())
//       throw ScopeError("No current scope available");
//     return scopes.back();
//   }

//   void setSymbol(const std::string &name, std::shared_ptr<Object> Object) { currentScope()->setSymbol(name, std::move(Object)); }

//   bool hasSymbol(const std::string &name) const {
//     if (imports.find(name) != imports.end())
//       return true;

//     for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
//       if ((*it)->hasSymbol(name))
//         return true;
//     }
//     return false;
//   }

//   std::shared_ptr<Object> getSymbol(const std::string &name) {
//     auto it_import = imports.find(name);
//     if (it_import != imports.end())
//       return it_import->second;

//     for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
//       if ((*it)->hasSymbol(name))
//         return (*it)->getSymbol(name);
//     }

//     throw SymbolNotFoundError(name);
//   }

//   void exportSymbol(const std::string &name, std::shared_ptr<Object> Object) { exports[name] = std::move(Object); }

//   void importAll(Environment &env) {
//     for (auto &pair : env.exports) {
//       imports[pair.first] = pair.second;
//     }
//   }
// };
