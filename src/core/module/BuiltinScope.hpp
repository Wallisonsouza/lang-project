#pragma once
#include "core/Arena.hpp"
#include "core/module/Scope.hpp"
#include "core/node/Type.hpp"
#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

namespace core {

class BuiltinScope {
  Scope scope;

public:
  BuiltinScope() : scope(nullptr) {
    inject_builtins();
    add_native_functions();
  }

  Scope *get_scope() { return &scope; }

private:
  void add_type(std::u32string name) {
    auto *type_node = scope.arena.create<node::TypeDeclarationNode>(
        name, std::vector<std::u32string>{});

    scope.declare(name, SymbolKind::Type, type_node, Visibility::Public, true);
  }

  void add_generic(std::u32string name,
                   std::initializer_list<std::u32string> params) {
    auto *type_node = scope.arena.create<node::TypeDeclarationNode>(
        name, std::vector<std::u32string>(params.begin(), params.end()));

    scope.declare(name, SymbolKind::Type, type_node, Visibility::Public, true);
  }

  void add_native_functions() {

    auto print_func = scope.arena.create<node::NativeFunctionNode>(
        U"print", std::vector<node::TypeNode *>{}, nullptr,
        [](const std::vector<core::node::Node *> &args) -> core::node::Node * {
          for (auto &arg : args) {

            std::cout << arg->to_string() << "\n";
          }
          return nullptr;
        });

    scope.declare(print_func->name, core::SymbolKind::Function, print_func,
                  core::Visibility::Public, true);
  }

  void add_native_operators() {

    // você pode continuar para Multiply, Divide etc.
  }

  void inject_builtins() {
    // primitivos
    add_type(U"Number");
    add_type(U"String");
    add_type(U"Bool");
    add_type(U"Void");

    // genéricos
    add_generic(U"Option", {U"T"});
    add_generic(U"Result", {U"T", U"E"});
    add_generic(U"Array", {U"T"});
  }
};

} // namespace core
