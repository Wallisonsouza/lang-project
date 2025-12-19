// #pragma once
// #include "core/module/Scope.hpp"
// #include "core/node/Node.hpp"
// #include "parser/Node.hpp"

// namespace resolver {

// // Forward declaration
// void resolve_node(core::node::Node *node, core::Scope &current_scope);

// inline void resolve_ast(const std::vector<core::node::Node *> &nodes, core::Scope &global_scope) {
//   for (auto *node : nodes) { resolve_node(node, global_scope); }
// }

// inline void resolve_node(core::node::Node *node, core::Scope &current_scope) {
//   if (!node) return;

//   using namespace parser;

//   if (auto var_decl = dynamic_cast<VariableDeclarationNode *>(node)) {
//     resolve_node(var_decl->type, current_scope);
//     resolve_node(var_decl->value, current_scope);

//     current_scope.add_variable(var_decl->name, var_decl, core::Visibility::Public);
//   }

//   else if (auto fn_decl = dynamic_cast<FunctionDeclarationNode *>(node)) {
//     current_scope.add_function(fn_decl->name, fn_decl, core::Visibility::Public);

//     core::Scope fn_scope(&current_scope);
//     for (auto &param : fn_decl->parameters) { fn_scope.add_variable(param.name, param.type, core::Visibility::Public); }

//     for (auto *stmt : fn_decl->body) { resolve_node(stmt, fn_scope); }
//   }
// }

// } // namespace resolver
