#pragma once
#include "core/node/Node.hpp"
#include <string>
#include <vector>

namespace core::node {

struct ExpressionNode : core::node::Node {};
struct StatementNode : core::node::Node {};

struct TypeDeclarationNode : core::node::Node {

  std::u32string name;
  std::vector<std::u32string> type_params;

  bool is_primitive = false;
  bool is_builtin = false;

  explicit TypeDeclarationNode(std::u32string n, std::vector<std::u32string> type_params = {}) : name(std::move(n)), type_params(type_params) {}
};

} // namespace core::node