#include "core/module/module.hpp"

namespace core {

Module::Module(const std::u32string name, Scope *parent_scope) : name(name), module_scope(parent_scope) {}

core::node::Node *Module::find(const std::u32string &name) {
  auto sym = module_scope.find(name);
  if (!sym || sym->visibility != core::Visibility::Public) { return nullptr; }
  return sym->declaration;
}
} // namespace core
