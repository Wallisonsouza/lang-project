#pragma once

#include "core/module/module.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace core {

using ModuleId = size_t;

struct ModuleManager {
  std::vector<Module> modules;
  std::unordered_map<std::string, ModuleId> root_modules;

  ModuleId create_module(const std::string &name,
                         ModuleId parent_id = SIZE_MAX) {
    ModuleId id = modules.size();
    modules.emplace_back(name, parent_id);
    if (parent_id == SIZE_MAX) {
      root_modules[name] = id;
    } else {
      modules[parent_id].children[name] = id;
    }
    return id;
  }

  Module *get(ModuleId id) { return &modules[id]; }

  ModuleId find_path(const std::vector<std::string> &path) {
    if (path.empty())
      return SIZE_MAX;

    auto it = root_modules.find(path[0]);
    if (it == root_modules.end())
      return SIZE_MAX;

    ModuleId current = it->second;
    for (size_t i = 1; i < path.size(); ++i) {
      auto child_it = modules[current].children.find(path[i]);
      if (child_it == modules[current].children.end())
        return SIZE_MAX;
      current = child_it->second;
    }

    return current;
  }

  const std::vector<Module> &get_all() const { return modules; }
};

} // namespace core
