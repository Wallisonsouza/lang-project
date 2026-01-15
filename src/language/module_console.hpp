#pragma once
#include "core/AST.hpp"
#include "core/module/module.hpp"
#include "core/node/Type.hpp"
#include "core/node/types.hpp"
#include "engine/language_context.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#define ANSI_RESET "\033[0m"
#define ANSI_GRAY "\033[37m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_RED "\033[31m"
#define ANSI_BOLD_GRAY "\033[1;37m"
#define ANSI_BOLD_YELLOW "\033[1;33m"
#define ANSI_BOLD_RED "\033[1;31m"

namespace ayla::modules {

inline core::node::IdentifierNode *id(AST &ast, const char *name) { return ast.create_node<core::node::IdentifierNode>(name); }

inline core::node::NativeFunctionDeclarationNode *
make_native(core::Module *module, core::node::IdentifierNode *name, std::vector<core::node::PatternNode *> params, core::node::TypeNode *return_type, Value::NativeFunction callback) {
  auto *node = module->ast.create_node<core::node::NativeFunctionDeclarationNode>(name, std::move(params), return_type, std::move(callback));
  module->ast.add_root(node);
  return node;
}

inline void create_module_console(LanguageContext &context, core::ModuleId parent = core::INVALID_MODULE) {
  core::ModuleId console_id = context.modules.create_module("console", parent);
  auto *module = context.modules.get(console_id);

  auto *void_return = module->ast.create_node<VoidTypeNode>();

  make_native(module, id(module->ast, "log"), {}, void_return, [](const std::vector<Value> &args) -> Value {
    std::cout << ANSI_BOLD_GRAY << "[log] " << ANSI_GRAY;
    for (auto &arg : args) std::cout << arg.convert_to_string();
    std::cout << ANSI_RESET << std::endl;
    return Value::Void();
  });

  make_native(module, id(module->ast, "warn"), {}, void_return, [](const std::vector<Value> &args) -> Value {
    std::cerr << ANSI_BOLD_YELLOW << "[warn] " << ANSI_YELLOW;
    for (auto &arg : args) std::cerr << arg.convert_to_string();
    std::cerr << ANSI_RESET << std::endl;
    return Value::Void();
  });

  make_native(module, id(module->ast, "error"), {}, void_return, [](const std::vector<Value> &args) -> Value {
    std::cerr << ANSI_BOLD_RED << "[error] " << ANSI_RED;
    for (auto &arg : args) std::cerr << arg.convert_to_string();
    std::cerr << ANSI_RESET << std::endl;
    return Value::Void();
  });
}

inline void create_module_math(LanguageContext &context, core::ModuleId parent = core::INVALID_MODULE) {
  core::ModuleId math_id = context.modules.create_module("math", parent);
  auto *module = context.modules.get(math_id);

  auto *number_type = module->ast.create_node<NumberTypeNode>();

  auto make_param = [&](const char *name) { return module->ast.create_node<core::node::PatternNode>(id(module->ast, name), number_type, nullptr); };

  make_native(module, id(module->ast, "abs"), {make_param("x")}, number_type, [](const std::vector<Value> &args) -> Value { return Value::Number(std::abs(args[0].get_number())); });

  make_native(module, id(module->ast, "sqrt"), {make_param("x")}, number_type, [](const std::vector<Value> &args) -> Value { return Value::Number(std::sqrt(args[0].get_number())); });

  make_native(module, id(module->ast, "sin"), {make_param("x")}, number_type, [](const std::vector<Value> &args) -> Value { return Value::Number(std::sin(args[0].get_number())); });

  make_native(module, id(module->ast, "cos"), {make_param("x")}, number_type, [](const std::vector<Value> &args) -> Value { return Value::Number(std::cos(args[0].get_number())); });

  make_native(module, id(module->ast, "random"), {}, number_type, [](const std::vector<Value> &) -> Value {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return Value::Number(dist(gen));
  });
}

} // namespace ayla::modules
