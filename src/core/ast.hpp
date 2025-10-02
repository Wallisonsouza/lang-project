#pragma once
#include "Environment.hpp"
#include <string>
#include <sys/types.h>
#include <variant>

using LanguagePrimitives = std::variant<int, float, std::string, char, std::shared_ptr<Node>>;

struct Node {
  virtual ~Node() = default;
  virtual LanguagePrimitives execute(Environment &env) = 0;
  virtual std::string toString() const = 0;
};