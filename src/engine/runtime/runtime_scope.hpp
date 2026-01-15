#pragma once
#include "core/memory/symbol.hpp"
#include "core/memory/value.hpp"
#include <unordered_map>

struct RuntimeScope {
  std::unordered_map<SymbolId, Value> values;
  RuntimeScope *parent;

  RuntimeScope(RuntimeScope *parent = nullptr) : parent(parent) {}

  void set(SymbolId id, Value val) { values[id] = val; }

  Value get(SymbolId id) {
    if (values.contains(id)) return values[id];
    if (parent) return parent->get(id);
    return Value::Null();
  }
};
