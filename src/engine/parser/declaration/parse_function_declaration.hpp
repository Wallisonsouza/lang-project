// #pragma once

// #include "core/node/Type.hpp"
// #include "core/token/Token.hpp"
// #include "core/token/TokenKind.hpp"
// #include "core/token/token_stream.hpp"
// #include "engine/CompilationUnit.hpp"
// #include "engine/parser/declaration/parse_modifiers.hpp"
// #include "engine/parser/match/match_block.hpp"
// #include "engine/parser/match/match_modifier.hpp"
// #include "engine/parser/match/match_parameter_list.hpp"
// #include "engine/parser/match/match_type.hpp"
// #include "engine/parser/node/statement_nodes.hpp"

// namespace parser::declaration {

// inline node::FunctionDeclarationNode *match_function_declaration(CompilationUnit &unit, core::token::TokenStream &stream, ExpressionParser &exp) {

//   auto mod = parser::declaration::parse_modifiers(stream);

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

//   auto params = match_parameter_list(unit, stream, exp);

//   core::node::TypeNode *return_type = nullptr;
//   auto next = stream.peek();
//   if (next && next->descriptor->kind == core::token::TokenKind::Arrow) {
//     stream.advance();
//     return_type = parse_type(unit, stream);
//     if (!return_type) {
//       stream.rollback_checkpoint();
//       return nullptr;
//     }
//   } else {
//     return_type = unit.ast.create_node<core::node::TypeNode>(U"void", false);
//   }

//   auto body = match_block(unit, stream, exp);
//   if (!body) {
//     stream.rollback_checkpoint();
//     return nullptr;
//   }

//   stream.discard_checkpoint();

//   return unit.ast.create_node<node::FunctionDeclarationNode>(unit.source.buffer.get_text(name_token->slice.span), std::move(params), return_type, body, mod);
// }

// } // namespace parser::declaration
