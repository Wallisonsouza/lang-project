#include "core/memory/Arena.hpp"
#include "core/module/scope.hpp"

class ScopeManager {
  core::memory::Arena arena;
  std::vector<core::Scope *> scopes;

public:
  core::Scope *create_scope(core::Scope *parent) {
    auto *scope = arena.alloc<core::Scope>(parent);
    scopes.push_back(scope);
    return scope;
  }
};
