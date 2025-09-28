#pragma once

#include <memory>
#include <string>
#include <unordered_map>

struct ASTNode;

class Scope {
  std::unordered_map<std::string, std::shared_ptr<ASTNode>> entries;

public:
  void setSymbol(const std::string &name, std::shared_ptr<ASTNode> value);
  std::shared_ptr<ASTNode> getSymbol(const std::string &name) const;
  bool hasSymbol(const std::string &name) const;
};
