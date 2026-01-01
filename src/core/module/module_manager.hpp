#pragma once
#include "core/memory/Arena.hpp"
#include "core/module/module.hpp"
#include <unordered_map>

namespace core {

struct ModuleManager {
private:
  core::memory::Arena arena;
  std::unordered_map<std::u32string, Module *> modules;

public:
  Module *create_module(const std::u32string &name, Scope *parent_scope);
  Module *find_path(const std::vector<std::u32string> &path);
};

} // namespace core