#pragma once
#include "core/module/module.hpp"
#include "core/node/Type.hpp"
#include "engine/language_context.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#define ANSI_RESET "\033[0m"
#define ANSI_GRAY "\033[37m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_RED "\033[31m"
#define ANSI_BOLD_GRAY "\033[1;37m"
#define ANSI_BOLD_YELLOW "\033[1;33m"
#define ANSI_BOLD_RED "\033[1;31m"

namespace ayla::modules {

inline core::node::NativeFunctionDeclarationNode *
make_native(core::Module *module, const std::string &name, std::vector<core::node::FunctionParameterNode *> params, core::node::TypeNode *return_type, core::node::native_callback callback) {
  auto node = module->ast.create_node<core::node::NativeFunctionDeclarationNode>(name, std::move(params), return_type, std::move(callback));
  module->ast.add_root(node);
  return node;
}

inline void create_module_console(LanguageContext &context, core::ModuleId parent = core::INVALID_MODULE) {
  core::ModuleId console_module_id = context.modules.create_module("console", parent);
  auto *module = context.modules.get(console_module_id);

  auto void_return = module->ast.create_node<core::node::VoidTypeNode>();

  make_native(module, "log", {}, void_return, [](const std::vector<Value> &args) -> Value {
    std::cout << ANSI_BOLD_GRAY << "[log] " << ANSI_GRAY;
    for (auto &arg : args) std::cout << arg.convert_to_string();
    std::cout << ANSI_RESET << std::endl;
    return Value::Void();
  });

  make_native(module, "warn", {}, void_return, [](const std::vector<Value> &args) -> Value {
    std::cerr << ANSI_BOLD_YELLOW << "[warn] " << ANSI_YELLOW;
    for (auto &arg : args) std::cerr << arg.convert_to_string();
    std::cerr << ANSI_RESET << std::endl;
    return Value::Void();
  });

  make_native(module, "error", {}, void_return, [](const std::vector<Value> &args) -> Value {
    std::cerr << ANSI_BOLD_RED << "[error] " << ANSI_RED;
    for (auto &arg : args) std::cerr << arg.convert_to_string();
    std::cerr << ANSI_RESET << std::endl;
    return Value::Void();
  });
}

inline void create_module_math(LanguageContext &context, core::ModuleId parent = core::INVALID_MODULE) {
  core::ModuleId math_module_id = context.modules.create_module("math", parent);
  auto *module = context.modules.get(math_module_id);

  auto number_type = module->ast.create_node<core::node::NumberTypeNode>();

  make_native(module, "abs", {module->ast.create_node<core::node::FunctionParameterNode>("x", number_type, nullptr)}, number_type,
              [](const std::vector<Value> &args) -> Value { return Value::Number(std::abs(args[0].get_number())); });

  make_native(module, "sqrt", {module->ast.create_node<core::node::FunctionParameterNode>("x", number_type, nullptr)}, number_type,
              [](const std::vector<Value> &args) -> Value { return Value::Number(std::sqrt(args[0].get_number())); });

  make_native(module, "sin", {module->ast.create_node<core::node::FunctionParameterNode>("x", number_type, nullptr)}, number_type,
              [](const std::vector<Value> &args) -> Value { return Value::Number(std::sin(args[0].get_number())); });

  make_native(module, "cos", {module->ast.create_node<core::node::FunctionParameterNode>("x", number_type, nullptr)}, number_type,
              [](const std::vector<Value> &args) -> Value { return Value::Number(std::cos(args[0].get_number())); });

  make_native(module, "random", {}, number_type, [](const std::vector<Value> &) -> Value {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);

    return Value::Number(dist(gen));
  });
}
} // namespace ayla::modules
