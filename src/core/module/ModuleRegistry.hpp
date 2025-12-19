#pragma once
#include "core/module/Module.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace core {
struct ModuleRegistry {
  std::unordered_map<std::u32string, std::unique_ptr<Module>> modules;

  Module *get_or_create(const std::u32string &full_name, Scope *root_parent);

private:
  Module *find(const std::u32string &full_name);

  std::pair<std::u32string, std::u32string> split_path(const std::u32string &full_name);

  Module *get_or_create_parent(const std::u32string &parent_name, Scope *root_parent);

  Module *create_module(const std::u32string &name, const std::u32string &full_name, Module *parent, Scope *parent_scope);
};

} // namespace core
