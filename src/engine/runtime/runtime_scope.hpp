#include "core/memory/symbol.hpp"
#include "core/node/Type.hpp"
#include <unordered_map>

struct RuntimeScope {
  std::unordered_map<SymbolId, Value> values;
  RuntimeScope *parent = nullptr;

  void set(SymbolId id, Value val) { values[id] = val; }

  Value get(SymbolId id) {
    if (values.contains(id)) return values[id];
    if (parent) return parent->get(id);
    return Value::Null();
  }
};
