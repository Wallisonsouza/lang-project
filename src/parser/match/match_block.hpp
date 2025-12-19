// #pragma once

// #include "core/CompilationUnit.hpp"
// #include "core/node/Type.hpp"
// #include "parser/ExpressionParser.hpp"
// #include "parser/Node.hpp"
// #include "parser/match/match_declaration.hpp"
// #include "parser/match/match_utils.hpp"

// namespace parser::match {

// inline BlockNode *match_block(CompilationUnit &unit, utils::Stream<core::token::Token *> &stream, ExpressionParser &exp) {

//   BlockNode *body;

//   if (!expect_token(unit, stream, core::token::TokenKind::OpenParen, "Expected '{' to start block")) { return body; }

//   while (!stream.eof()) {
//     auto tok = stream.peek();
//     if (!tok) break;
//     if (tok->descriptor->kind == core::token::TokenKind::CloseBrace) {
//       stream.advance();
//       break;
//     }

//     auto *stmt = match_declaration(unit, stream, exp);

//     if (!stmt) {
//       // Pode ser uma expressão sozinha
//       // parser::ExpressionNode *expr = exp.parse(unit.ast, unit, stream);
//       // if (expr) { stmt = unit.ast.create_node<parser::ExpressionStatementNode>(expr); }
//     }

//     if (stmt) {

//     }
//     // body->statements.push_back(stmt);
//     else
//       break; // erro de parse
//   }

//   return body;
// }
// } // namespace parser::match
