#pragma once
#include "Module.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace core {

struct ModuleRegistry {

  std::unordered_map<std::u32string, std::unique_ptr<Module>> modules;

  Module *find(const std::u32string &full_name) const {
    auto it = modules.find(full_name);
    return it != modules.end() ? it->second.get() : nullptr;
  }

  static std::pair<std::u32string, std::u32string>
  split_path(const std::u32string &full_name) {
    auto pos = full_name.rfind(U".");
    if (pos == std::u32string::npos) return {U"", full_name};
    return {full_name.substr(0, pos), full_name.substr(pos + 1)};
  }

  Module *create_module(const std::u32string &name,
                        const std::u32string &full_name) {

    auto mod = std::make_unique<Module>(name, full_name, nullptr);
    Module *ptr = mod.get();
    modules.emplace(full_name, std::move(mod));
    return ptr;
  }

  Module *get_or_create(const std::u32string &full_name) {
    if (auto *existing = find(full_name)) return existing;

    auto [parent_name, name] = split_path(full_name);

    return create_module(name, full_name);
  }

  void register_alias(const std::u32string &alias,
                      const std::u32string &target_full_name,
                      std::unordered_map<std::u32string, Module *> &alias_map) {
    if (auto *target = find(target_full_name)) {
      alias_map[alias] = target;
    }
  }
};

} // namespace core
