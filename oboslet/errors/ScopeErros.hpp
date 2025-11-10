// #pragma once
// #include <stdexcept>

// class ScopeError : public std::runtime_error {
// public:
//   explicit ScopeError(const std::string &msg) : std::runtime_error(msg) {}
// };

// class SymbolAlreadyExistsError : public ScopeError {
// public:
//   explicit SymbolAlreadyExistsError(const std::string &name)
//       : ScopeError("Variable already exists: " + name) {}
// };

// class FunctionAlreadyExistsError : public ScopeError {
// public:
//   explicit FunctionAlreadyExistsError(const std::string &name)
//       : ScopeError("Function already exists: " + name) {}
// };

// class SymbolNotFoundError : public ScopeError {
// public:
//   explicit SymbolNotFoundError(const std::string &name)
//       : ScopeError("Variable not found: " + name) {}
// };

// class FunctionNotFoundError : public ScopeError {
// public:
//   explicit FunctionNotFoundError(const std::string &name)
//       : ScopeError("Function not found: " + name) {}
// };
