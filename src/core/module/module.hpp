#pragma once

#include "core/module/scope.hpp"
#include "core/node/Node.hpp"
#include <string>

namespace core {

struct Module {
  std::u32string name;
  Scope module_scope;

  Module(std::u32string name, Scope *parent_scope);

  core::node::Node *find(const std::u32string &name);
};

} // namespace core
