#pragma once

#include <memory>
#include <string>
#include <unordered_map>

struct Node;

class Scope {
  std::unordered_map<std::string, std::shared_ptr<Node>> entries;

public:
  void setSymbol(const std::string &name, std::shared_ptr<Node> value);
  std::shared_ptr<Node> getSymbol(const std::string &name) const;
  bool hasSymbol(const std::string &name) const;
};
