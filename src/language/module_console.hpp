#pragma once
#include "core/module/module.hpp"
#include "core/module/module_manager.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include <iostream>

namespace ayla::modules {

inline core::node::NativeFunctionDeclarationNode *
make_native(core::Module *module, const std::u32string &name, std::vector<core::node::FunctionParameterNode *> params, core::node::TypeNode *return_type, auto callback) {

  auto func = module->module_scope.arena.create<core::node::NativeFunctionDeclarationNode>(name, params, return_type, callback);

  module->module_scope.declare(func->name, core::SymbolKind::Function, func, core::Visibility::Public, true);
  return func;
};

inline void create_module_console(core::ModuleManager &manager) {

  auto module = manager.create_module(U"debug.console", nullptr);

  std::vector<core::node::FunctionParameterNode *> params;
  core::node::TypeNode *return_type = module->module_scope.arena.create<core::node::VoidTypeNode>();

  make_native(module, U"log", params, return_type, [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
    for (size_t i = 0; i < args.size(); ++i) {
      auto *arg = args[i];
      if (arg) std::cout << arg->to_string();
      if (i + 1 < args.size()) std::cout << " ";
    }
    std::cout << std::endl;
    return nullptr;
  });

  make_native(module, U"print", params, return_type, [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
    for (size_t i = 0; i < args.size(); ++i) {
      auto *arg = args[i];
      if (arg) std::cout << arg->to_string();
      if (i + 1 < args.size()) std::cout << " ";
    }
    std::cout << std::endl;
    return nullptr;
  });

  make_native(module, U"warn", params, return_type, [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
    for (size_t i = 0; i < args.size(); ++i) {
      auto *arg = args[i];
      if (arg) std::cerr << arg->to_string();
      if (i + 1 < args.size()) std::cerr << " ";
    }
    std::cerr << std::endl;
    return nullptr;
  });

  make_native(module, U"error", params, return_type, [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
    for (size_t i = 0; i < args.size(); ++i) {
      auto *arg = args[i];
      if (arg) std::cerr << arg->to_string();
      if (i + 1 < args.size()) std::cerr << " ";
    }
    std::cerr << std::endl;
    return nullptr;
  });
}

} // namespace ayla::modules
