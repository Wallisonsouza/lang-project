// resolver/ResolveVariable.cpp
#include "Resolver.hpp"
#include "core/node/Type.hpp"
#include "utils/Utf8.hpp"

namespace resolver {

inline void resolve_type(Resolver &ctx, core::node::TypeNode *type_node) {
  if (!type_node)
    return;

  core::Symbol *sym = ctx.current_scope->find(type_node->name);

  if (!sym) {
    ctx.error("Tipo '" + utils::Utf::utf32to8(type_node->name) +
              "' não declarado");
    return;
  }

  type_node->symbol = sym;

  for (auto *generic : type_node->generics) {
    resolve_type(ctx, generic);
  }
}

} // namespace resolver