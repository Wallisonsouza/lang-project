#pragma once
#include "core/node/Node.hpp"
#include <cstdint>
#include <string>

enum class Visibility { Private, Public };

enum class SymbolKind {
  Type,
  Function,
  Variable,
};

struct Symbol {
  std::string name;
  SymbolKind kind;
  Visibility visibility;
  bool is_builtin;
  core::node::Node *declaration = nullptr;

  Symbol(std::string name, SymbolKind kind,
         Visibility visibility = Visibility::Private, bool is_builtin = false,
         core::node::Node *decl = nullptr)
      : name(std::move(name)), kind(kind), visibility(visibility),
        is_builtin(is_builtin) {}
};

using SymbolId = size_t;
inline constexpr SymbolId INVALID_SYMBOL_ID = SIZE_MAX;