// resolver/ResolveVariable.cpp
#include "Resolver.hpp"
#include "parser/node/statement_nodes.hpp"
#include "utils/Utf8.hpp"

namespace resolver {

inline void resolve_variable_declaration(Resolver &ctx,
                                         node::VariableDeclarationNode *var) {
  if (!var)
    return;

  if (var->value)
    ctx.resolve(var->value);
  if (var->type)
    ctx.resolve(var->type);

  auto *sym = ctx.current_scope->declare(
      var->name, core::SymbolKind::Variable, var,
      core::node::hasModifier(var->modifiers, core::node::Modifier::Public)
          ? core::Visibility::Public
          : core::Visibility::Private);

  if (!sym) {
    ctx.error("variável '" + utils::Utf::utf32to8(var->name) +
              "' já declarada neste escopo");
    return;
  }

  var->symbol = sym;
}

} // namespace resolver
