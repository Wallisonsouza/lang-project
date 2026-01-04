#pragma once
#include "core/module/module.hpp"

#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include <iostream>
#include <string>

#define ANSI_RESET "\033[0m"

#define ANSI_GRAY "\033[37m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_RED "\033[31m"

#define ANSI_BOLD_GRAY "\033[1;37m"
#define ANSI_BOLD_YELLOW "\033[1;33m"
#define ANSI_BOLD_RED "\033[1;31m"

namespace ayla::modules {

inline void make_native(CompilationUnit &unit, core::ModuleId module_id,
                        const std::string &name,
                        std::vector<core::node::FunctionParameterNode *> params,
                        core::node::TypeNode *return_type,
                        core::node::native_callback callback) {

  auto func = unit.ast.create_node<core::node::NativeFunctionDeclarationNode>(
      name, params, return_type, callback);

  auto symbol_id = unit.symbols.create_symbol(func->name, SymbolKind::Function,
                                              Visibility::Public, true, func);

  auto symbol = unit.symbols.get(symbol_id);
  symbol->declaration = func;

  auto module = unit.modules.get(module_id);

  module->module_scope.add_symbol(func->name, symbol_id);
};

inline void create_module_console(CompilationUnit &unit) {

  core::ModuleId debug_module = unit.modules.create_module("debug");
  core::ModuleId console_module =
      unit.modules.create_module("console", debug_module);

  std::vector<core::node::FunctionParameterNode *> params;

  auto void_return = unit.ast.create_node<core::node::VoidTypeNode>();

  make_native(unit, console_module, "log", params, void_return,
              [](const std::vector<Value> &args) -> Value {
                std::cout << ANSI_BOLD_GRAY << "[log] " << ANSI_GRAY;

                for (auto &arg : args) {
                  std::cout << arg.convert_to_string();
                }

                std::cout << ANSI_RESET << std::endl;
                return Value::Void();
              });

  make_native(unit, console_module, "warn", params, void_return,
              [](const std::vector<Value> &args) -> Value {
                std::cerr << ANSI_BOLD_YELLOW << "[warn] " << ANSI_YELLOW;

                for (auto &arg : args) {
                  std::cerr << arg.convert_to_string();
                }

                std::cerr << ANSI_RESET << std::endl;
                return Value::Void();
              });

  make_native(unit, console_module, "error", params, void_return,
              [](const std::vector<Value> &args) -> Value {
                std::cerr << ANSI_BOLD_RED << "[error] " << ANSI_RED;

                for (auto &arg : args) {
                  std::cerr << arg.convert_to_string();
                }

                std::cerr << ANSI_RESET << std::endl;
                return Value::Void();
              });
}

} // namespace ayla::modules
