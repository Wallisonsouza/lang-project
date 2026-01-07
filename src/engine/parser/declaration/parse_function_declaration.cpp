// #include "core/node/Node.hpp"
// #include "core/node/Type.hpp"
// #include "engine/parser/node/statement_nodes.hpp"
// #include "engine/parser/parser.hpp"

// core::node::StatementNode *Parser::parse_function_declaration() {

//   auto mod = parse_modifiers();

//   stream.add_checkpoint();

//   auto keyword = stream.peek();
//   if (!keyword || keyword->descriptor->kind != core::token::TokenKind::FunctionKeyword) {
//     stream.rollback_checkpoint();
//     return nullptr;
//   }
//   stream.advance();

//   auto name_token = stream.peek();
//   if (!name_token || name_token->descriptor->kind != core::token::TokenKind::Identifier) {
//     stream.rollback_checkpoint();
//     return nullptr;
//   }
//   stream.advance();

//   auto params = parse_parameter_list();

//   core::node::TypeNode *return_type = nullptr;
//   auto next = stream.peek();
//   if (next && next->descriptor->kind == core::token::TokenKind::Arrow) {
//     stream.advance();
//     return_type = parse_type();
//     if (!return_type) {
//       stream.rollback_checkpoint();
//       return nullptr;
//     }
//   } else {
//     return_type = unit.ast.create_node<core::node::VoidTypeNode>();
//   }

//   // auto body = match_block(unit, stream, exp);

//   core::node::Node *body = nullptr;

//   if (!body) {
//     stream.rollback_checkpoint();
//     return nullptr;
//   }

//   stream.discard_checkpoint();

//   return unit.ast.create_node<parser::node::FunctionDeclarationNode>(unit.source.buffer.get_text(name_token->slice.span), std::move(params), return_type, body, mod);
// }
