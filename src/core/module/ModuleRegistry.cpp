#include "ModuleRegistry.hpp"
#include "core/module/Scope.hpp"

namespace core {

Module *ModuleRegistry::find(const std::u32string &full_name) {
  auto it = modules.find(full_name);
  return it != modules.end() ? it->second.get() : nullptr;
}

std::pair<std::u32string, std::u32string> ModuleRegistry::split_path(const std::u32string &full_name) {
  auto pos = full_name.rfind(U"::");
  if (pos == std::u32string::npos) return {U"", full_name};

  return {full_name.substr(0, pos), full_name.substr(pos + 2)};
}

Module *ModuleRegistry::get_or_create_parent(const std::u32string &parent_name, Scope *root_parent) {

  if (parent_name.empty()) return nullptr;

  return get_or_create(parent_name, root_parent);
}

Module *ModuleRegistry::create_module(const std::u32string &name, const std::u32string &full_name, Module *parent, Scope *parent_scope) {

  auto mod = std::make_unique<Module>(name, full_name, parent_scope);
  Module *ptr = mod.get();

  ptr->parent = parent;
  if (parent) parent->children[name] = ptr;

  modules.emplace(full_name, std::move(mod));
  return ptr;
}

Module *ModuleRegistry::get_or_create(const std::u32string &full_name, Scope *root_parent) {

  if (auto *existing = find(full_name)) return existing;

  auto [parent_name, name] = split_path(full_name);

  Module *parent = get_or_create_parent(parent_name, root_parent);
  Scope *parent_scope = parent ? &parent->module_scope : root_parent;

  return create_module(name, full_name, parent, parent_scope);
}

} // namespace core
