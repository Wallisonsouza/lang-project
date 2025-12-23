// #include "Resolver.hpp"
// #include "core/AST.hpp"
// #include "core/node/NodeKind.hpp"
// #include "core/node/Type.hpp"
// #include "parser/node/literal_nodes.hpp"
// #include "parser/node/statement_nodes.hpp"
// #include "resolve_identifier.hpp"
// #include "resolve_type.hpp"
// #include "resolve_variable_declaration.hpp"
// #include "resolver_function_call.hpp"
// #include <iostream>

// namespace resolver {

// void Resolver::resolve(core::node::Node *node) {
//   if (!node)
//     return;

//   switch (node->kind) {

//   case core::node::NodeKind::VariableDeclaration:
//     resolve_variable_declaration(
//         *this, static_cast<node::VariableDeclarationNode *>(node));
//     break;
//   case core::node::NodeKind::Identifier:
//     resolve_identifier(*this, static_cast<node::IdentifierNode *>(node));
//     break;
//   case core::node::NodeKind::Type:
//     resolve_type(*this, static_cast<core::node::TypeNode *>(node));

//   case core::node::NodeKind::FunctionCall:
//     resolve_function_call(*this, static_cast<node::FunctionCallNode
//     *>(node)); break;
//   default:
//     break;
//   }
// }

// void Resolver::resolve_ast(AST &ast) {
//   for (auto &node : ast.get_nodes()) {
//     resolve(node);
//   }
// }

// void Resolver::error(const std::string &msg) {
//   std::cerr << "erro: " << msg << "\n";
// }

// } // namespace resolver
