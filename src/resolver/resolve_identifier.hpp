// resolver/ResolveIdentifier.cpp
#include "Resolver.hpp"
#include "parser/node/literal_nodes.hpp"
#include "utils/Utf8.hpp"

namespace resolver {

inline void resolve_identifier(Resolver &ctx, node::IdentifierNode *id) {
  core::Symbol *sym = ctx.current_scope->find(id->name);

  if (!sym) {
    ctx.error("símbolo não declarado '" + utils::Utf::utf32to8(id->name) + "'");
    return;
  }

  id->symbol = sym;
}

} // namespace resolver
