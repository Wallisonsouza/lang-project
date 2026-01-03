// #pragma once
// #include "core/token/TokenKind.hpp"
// #include "core/token/token_stream.hpp"
// #include "engine/CompilationUnit.hpp"
// #include "engine/parser/ExpressionParser.hpp"
// #include "engine/parser/match/match_statement.hpp"
// #include "engine/parser/node/statement_nodes.hpp"

// namespace parser::match {

// inline node::BlockNode *match_block(CompilationUnit &unit, core::token::TokenStream &stream, ExpressionParser &exp) {

//   auto open = stream.peek();
//   if (!open || open->descriptor->kind != core::token::TokenKind::OpenBrace) { return nullptr; }

//   stream.advance(); // consome '{'

//   std::vector<core::node::StatementNode *> statements;

//   while (!stream.is_end()) {
//     auto tok = stream.peek();

//     if (tok && tok->descriptor->kind == core::token::TokenKind::CloseBrace) {
//       stream.advance(); // consome '}'
//       return unit.ast.create_node<node::BlockNode>(std::move(statements));
//     }

//     auto stmt = match_statement(unit, stream, exp);
//     if (!stmt) { return unit.ast.create_node<node::BlockNode>(std::move(statements)); }

//     statements.push_back(stmt);
//   }

//   return unit.ast.create_node<node::BlockNode>(std::move(statements));
// }

// } // namespace parser::match
