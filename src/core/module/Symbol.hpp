#pragma once
#include "core/node/Node.hpp"
#include <string>

namespace core {

enum class Visibility { Private, Public };

enum class SymbolKind {
  Type,
  Function,
  Variable,
};

struct Symbol {
  std::u32string name;
  SymbolKind kind;
  node::Node *declaration;
  Visibility visibility;
  bool is_builtin;

  Symbol(std::u32string name, SymbolKind kind, node::Node *declaration,
         Visibility visibility = Visibility::Private, bool is_builtin = false)
      : name(std::move(name)), kind(kind), declaration(declaration),
        visibility(visibility), is_builtin(is_builtin) {}
};
} // namespace core