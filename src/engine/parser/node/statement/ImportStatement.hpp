#pragma once
#include "core/node/Type.hpp"
#include <optional>
#include <string>
#include <vector>

namespace parser::node::statement {

struct ImportNode : core::node::StatementNode {
  std::vector<std::u32string> path;
  std::optional<std::u32string> alias;

  explicit ImportNode(std::vector<std::u32string> p) : StatementNode(core::node::NodeKind::ImportStatement), path(std::move(p)) {}
};

} // namespace parser::node::statement
