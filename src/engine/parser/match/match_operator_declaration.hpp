// #pragma once
// #include "core/CompilationUnit.hpp"
// #include "core/TokenStream.hpp"
// #include "core/node/Type.hpp"
// #include "core/token/TokenGroup.hpp"
// #include "core/token/TokenKind.hpp"
// #include "parser/ExpressionParser.hpp"
// #include "parser/match/match_function_parameter.hpp"
// #include "parser/match/match_modifier.hpp"
// #include "parser/match/match_parameter_list.hpp"
// #include "parser/match/match_type.hpp"
// #include "parser/node/literal_nodes.hpp"
// #include "parser/node/statement_nodes.hpp"
// namespace parser::match {

// inline node::OperatorDeclarationNode *
// match_operator_declaration(CompilationUnit &unit, TokenStream &stream,
//                            ExpressionParser &exp) {
//   stream.push_checkpoint();

//   auto keyword = stream.peek();
//   if (!keyword ||
//       keyword->descriptor->kind != core::token::TokenKind::OperatorKeyword) {
//     stream.rollback_checkpoint();
//     return nullptr;
//   }
//   stream.advance();

//   auto opTok = stream.peek();
//   if (!opTok || opTok->descriptor->group !=
//   core::token::TokenGroup::Operator) {
//     stream.rollback_checkpoint();
//     return nullptr;
//   }

//   auto operator_kind = opTok->descriptor->kind;

//   stream.advance();

//   auto params = match_parameter_list(unit, stream, exp);

//   // 4️⃣ tipo de retorno
//   core::node::TypeNode *return_type = nullptr;
//   if (stream.match(core::token::TokenKind::Arrow)) {
//     return_type = match_type(unit, stream);
//     if (!return_type) {
//       unit.error(stream.peek(), "Expected return type after '->'");
//       stream.rollback_checkpoint();
//       return nullptr;
//     }
//   }

//   // 5️⃣ corpo
//   auto body = match_block(unit, stream);
//   if (!body) {
//     stream.rollback_checkpoint();
//     return nullptr;
//   }

//   return unit.ast.create<node::OperatorDeclarationNode>(
//       operator_kind, std::move(*params), return_type, body);
// }

// } // namespace parser::match
