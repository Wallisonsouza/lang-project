// resolver/Resolver.hpp
#pragma once
#include "core/AST.hpp"
#include "core/module/Scope.hpp"
#include "core/node/Node.hpp"

namespace resolver {

struct Resolver {
  core::Scope *current_scope;

  explicit Resolver(core::Scope *global) : current_scope(global) {}

  void resolve(core::node::Node *node);
  void resolve_ast(AST &ast);
  // utilitários comuns
  void error(const std::string &msg);
  void push_scope();
  void pop_scope();
};

} // namespace resolver
