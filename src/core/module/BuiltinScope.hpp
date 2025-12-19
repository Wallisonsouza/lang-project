#pragma once
#include "core/Arena.hpp"
#include "core/module/Scope.hpp"
#include "core/node/Type.hpp"
#include <string>
#include <vector>

namespace core {
class BuiltinScope : public Scope {
  core::memory::Arena ast_arena;

public:
  BuiltinScope() : Scope(nullptr) { inject_builtins(); }

private:
  void add_primitive(std::u32string name) {
    auto t = ast_arena.create<node::TypeDeclarationNode>(name, std::vector<std::u32string>());
    t->is_builtin = true;
    t->is_primitive = true;

    add_type(name, t, Visibility::Public);
  }

  void add_generic(std::u32string name, std::initializer_list<std::u32string> params) {
    auto t = ast_arena.create<node::TypeDeclarationNode>(name, std::vector<std::u32string>());
    t->is_builtin = true;
    t->type_params.assign(params.begin(), params.end());

    add_type(name, t, Visibility::Public);
  }

  void inject_builtins() {

    add_primitive(U"Number");
    add_primitive(U"String");
    add_primitive(U"Bool");
    add_primitive(U"Void");

    add_generic(U"Option", {U"T"});
    add_generic(U"Result", {U"T", U"E"});
    add_generic(U"Array", {U"T"});
  }
};
} // namespace core
