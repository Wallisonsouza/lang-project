// #pragma once

// #include "core/node/Type.hpp"
// #include "core/token/TokenKind.hpp"
// #include "core/token/token_stream.hpp"
// #include "engine/CompilationUnit.hpp"
// #include "engine/parser/ExpressionParser.hpp"
// #include "engine/parser/match/match_function_parameter.hpp"
// #include "engine/parser/match/match_utils.hpp"

// namespace parser::match {
// inline std::vector<core::node::FunctionParameterNode *> match_parameter_list(CompilationUnit &unit, core::token::TokenStream &stream, ExpressionParser &exp) {
//   std::vector<core::node::FunctionParameterNode *> params;

//   if (!expect_token(unit, stream, core::token::TokenKind::OpenParen, "Expected '('")) { return params; }

//   while (!stream.is_end()) {
//     auto param = match_function_parameter(unit, stream, exp);
//     if (!param) break;

//     params.push_back(param);

//     auto comma = stream.peek();
//     if (comma && comma->descriptor->kind == core::token::TokenKind::Comma) {
//       stream.advance();
//       continue;
//     }

//     break;
//   }

//   if (!expect_token(unit, stream, core::token::TokenKind::CloseParen, "Expected ')' after parameters")) { return params; }

//   return params;
// }

// } // namespace parser::match
