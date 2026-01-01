#include "module_manager.hpp"

namespace core {

Module *ModuleManager::create_module(const std::u32string &name, Scope *parent_scope) {
  Module *mod = arena.create<Module>(name, parent_scope);
  modules[name] = mod;
  return mod;
}

Module *ModuleManager::find_path(const std::vector<std::u32string> &path) {
  if (path.empty()) return nullptr;

  std::u32string full;
  for (size_t i = 0; i < path.size(); ++i) {
    if (i > 0) full += U".";
    full += path[i];
  }

  auto it = modules.find(full);
  return it != modules.end() ? it->second : nullptr;
}

} // namespace core