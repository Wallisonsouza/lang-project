#pragma once

#include <stdexcept>

class EnvironmentError : public std::runtime_error {
public:
  explicit EnvironmentError(const std::string &message)
      : std::runtime_error(message) {}
};

class SymbolNotFoundError : public EnvironmentError {
public:
  explicit SymbolNotFoundError(const std::string &name)
      : EnvironmentError("Variável não encontrada: " + name) {}
};

class FunctionNotFoundError : public EnvironmentError {
public:
  explicit FunctionNotFoundError(const std::string &name)
      : EnvironmentError("Função não encontrada: " + name) {}
};

class ScopeError : public EnvironmentError {
public:
  explicit ScopeError(const std::string &message) : EnvironmentError(message) {}
};