// #pragma once
// #include "core/AST.hpp"
// #include "core/CompilationUnit.hpp"
// #include "core/node/Node.hpp"
// #include "core/node/Type.hpp"

// #include "core/token/Token.hpp"
// #include "utils/Stream.hpp"

// namespace parser::match {

// inline core::node::Node *match_type_declaration(CompilationUnit &unit,
// utils::Stream<core::token::Token *> &stream) {

//   // auto keyword = stream.peek();
//   // if (!keyword || keyword->descriptor->kind !=
//   core::token::TokenKind::TypeKeyword) return nullptr;

//   // auto tok = stream.peek();
//   // if (!tok || tok->descriptor->kind != core::token::TokenKind::Identifier)
//   return nullptr;

//   // std::u32string name = unit.source.buffer.get_text(tok->span);
//   // stream.advance();

//   // std::vector<std::u32string> type_params;

//   // auto next = stream.peek();
//   // if (next && next->descriptor->kind == core::token::TokenKind::LessThan)
//   {
//   //   stream.advance();
//   //   while (true) {
//   //     auto param = stream.peek();
//   //     if (!param || param->descriptor->kind !=
//   core::token::TokenKind::Identifier) break;
//   //     type_params.push_back(unit.source.buffer.get_text(param->span));
//   //     stream.advance();

//   //     auto comma = stream.peek();
//   //     if (comma && comma->descriptor->kind ==
//   core::token::TokenKind::Comma)
//   //       stream.advance();
//   //     else
//   //       break;
//   //   }

//   //   auto gt = stream.peek();
//   //   if (gt && gt->descriptor->kind == core::token::TokenKind::GreaterThan)
//   //     stream.advance();
//   //   else
//   //     type_params.push_back(U"<missing>");
//   // }

//   // return unit.ast.create_node<core::node::TypeDeclarationNode>(name,
//   type_params); return nullptr;
// }

// } // namespace parser::match
