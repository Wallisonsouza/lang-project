// #include "Resolver.hpp"
// #include "core/module/Symbol.hpp"
// #include "parser/node/literal_nodes.hpp"
// #include "parser/node/statement_nodes.hpp"
// #include "utils/Utf8.hpp"

// namespace resolver {

// inline void resolve_function_call(Resolver &ctx, node::FunctionCallNode
// *call) {
//   if (!call)
//     return;

//   ctx.resolve(call->callee);

//   for (auto *arg : call->args) {
//     ctx.resolve(arg);
//   }

//   if (auto *id = static_cast<node::IdentifierNode *>(call->callee)) {

//     core::Symbol *sym = ctx.current_scope->find(id->name);

//     if (!sym) {
//       ctx.error("Função '" + utils::Utf::utf32to8(id->name) +
//                 "' não encontrada");
//       return;
//     }

//     if (sym->kind != core::SymbolKind::Function) {
//       ctx.error("'" + utils::Utf::utf32to8(id->name) + "' não é uma função");
//       return;
//     }

//     call->symbol = sym;
//   } else {
//     ctx.error("Callee deve ser uma função identificável");
//   }
// }

// } // namespace resolver
