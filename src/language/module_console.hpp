#pragma once
#include "core/module/Module.hpp"
#include "core/module/Scope.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include <iostream>

namespace ayla::modules::console {

inline void create_module_console(core::Module &module) {
  std::vector<core::node::FunctionParameterNode *> params;
  core::node::TypeNode *return_type =
      module.module_scope.arena.create<core::node::VoidTypeNode>();

  auto make_native =
      [&](const std::u32string &name,
          auto callback) -> core::node::NativeFunctionDeclarationNode * {
    auto func = module.module_scope.arena
                    .create<core::node::NativeFunctionDeclarationNode>(
                        name, params, return_type, callback);
    module.module_scope.declare(func->name, core::SymbolKind::Function, func,
                                core::Visibility::Public, true);
    return func;
  };

  make_native(
      U"print",
      [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
        for (size_t i = 0; i < args.size(); ++i) {
          auto *arg = args[i];
          if (arg) std::cout << arg->to_string();
          if (i + 1 < args.size()) std::cout << " ";
        }
        std::cout << std::endl;
        return nullptr;
      });

  make_native(
      U"warn",
      [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
        for (size_t i = 0; i < args.size(); ++i) {
          auto *arg = args[i];
          if (arg) std::cerr << arg->to_string();
          if (i + 1 < args.size()) std::cerr << " ";
        }
        std::cerr << std::endl;
        return nullptr;
      });

  make_native(
      U"error",
      [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
        for (size_t i = 0; i < args.size(); ++i) {
          auto *arg = args[i];
          if (arg) std::cerr << arg->to_string();
          if (i + 1 < args.size()) std::cerr << " ";
        }
        std::cerr << std::endl;
        return nullptr;
      });
}

} // namespace ayla::modules::console
