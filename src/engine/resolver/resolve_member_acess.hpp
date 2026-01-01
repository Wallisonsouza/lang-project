// #pragma once

// #include "Resolver.hpp"
// #include "core/module/module.hpp"
// #include "core/node/NodeKind.hpp"
// #include "engine/CompilationUnit.hpp"
// #include "engine/parser/node/literal_nodes.hpp"
// #include "engine/parser/node/statement_nodes.hpp"
// #include "utils/Utf8.hpp"
// #include <stdexcept>

// namespace resolver {

// inline void resolve_member_access(CompilationUnit &unit, Resolver &resolver, parser::node::MemberAccessNode *node) {

//   resolver.resolve(unit, node->object);

//   switch (node->property->kind) {
//   case core::node::NodeKind::Identifier: break;

//   default: break;
//   }

//   auto *prop_id = dynamic_cast<parser::node::IdentifierNode *>(node->property);

//   if (!prop_id) {
//     throw std::runtime_error("membro inválido (esperado identificador)");
//     return;
//   }

//   if (auto *obj_id = dynamic_cast<parser::node::IdentifierNode *>(node->object)) {

//     core::Symbol *base_sym = resolver.current_scope->find(obj_id->name);

//     if (!base_sym) {
//       throw std::runtime_error("símbolo '" + utils::Utf::utf32to8(obj_id->name) + "' não encontrado");
//       return;
//     }

//     // if (base_sym->kind == core::SymbolKind::Module) {
//     //   auto *module = static_cast<core::Module *>(base_sym->declaration);

//     //   core::Symbol *member = module->module_scope.find(prop_id->name);

//     //   if (!member || member->visibility != core::Visibility::Public) {
//     //     throw std::runtime_error("membro '" + utils::Utf::utf32to8(prop_id->name) + "' não existe no módulo '" + utils::Utf::utf32to8(obj_id->name) + "'");
//     //     return;
//     //   }

//     //   node->symbol = member;
//     //   return;
//     // }

//     // 5️⃣ Outros casos virão depois (struct, enum, type)
//     throw std::runtime_error("tipo não suporta acesso a membros");
//     return;
//   }

//   // 6️⃣ Caso encadeado: (a.b).c
//   if (auto *inner = dynamic_cast<parser::node::MemberAccessNode *>(node->object)) {

//     core::Symbol *base = inner->symbol;

//     if (!base) {
//       throw std::runtime_error("acesso a membro inválido");
//       return;
//     }

//     // Exemplo futuro:
//     // struct / namespace / type scope
//     throw std::runtime_error("acesso encadeado ainda não suportado");
//     return;
//   }

//   throw std::runtime_error("expressão não suporta acesso a membros");
// }

// } // namespace resolver
