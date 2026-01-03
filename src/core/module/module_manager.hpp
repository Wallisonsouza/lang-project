#pragma once
#include "module.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace core {

struct ModuleManager {
  core::memory::Arena arena;
  std::unordered_map<std::string, Module *> root_modules;

  Module *create_module(const std::string &name,
                        Module *parent_module = nullptr) {
    auto *mod = arena.create<Module>(name, parent_module);
    if (!parent_module) {
      root_modules[name] = mod;
    } else {
      parent_module->add_child(mod);
    }
    return mod;
  }

  Module *find_path(const std::vector<std::string> &path) {
    if (path.empty())
      return nullptr;

    Module *current = nullptr;

    auto it = root_modules.find(path[0]);
    if (it == root_modules.end())
      return nullptr;
    current = it->second;

    for (size_t i = 1; i < path.size(); ++i) {
      auto child_it = current->children.find(path[i]);
      if (child_it == current->children.end())
        return nullptr;
      current = child_it->second;
    }

    return current;
  }
};

} // namespace core
