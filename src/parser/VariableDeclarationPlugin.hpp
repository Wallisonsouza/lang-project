// #pragma once

// #include "core/lexer/Lexer.hpp"
// #include "core/parser/Parser.hpp"
// #include "core/parser/ParserPlugin.hpp"
// #include "core/token/Token.hpp"
// #include "core/token/TokenGroup.hpp"
// #include "core/token/TokenKind.hpp"
// #include "core/utils/Stream.hpp"
// #include <memory>

// namespace interpreter::parser::plugins {

// class VariableDeclarationPlugin : public ParserPlugin {
// public:
//   std::shared_ptr<Node> match(Parser &parser,
//                               core::Stream<core::Token> &stream) override {

//     stream.push();

//     auto &data = parser.get_data();

//     auto ident = stream.peek(0);
//     if (!ident || ident->descriptor->kind != core::TokenKind::Identifier) {
//       stream.pop_restore();
//       return nullptr;
//     }

//     auto colon = stream.peek(1);

//     if (!colon || colon->descriptor->kind != core::TokenKind::Colon) {
//       parser.diag.report("Expected ':' after identifier",
//                          "Variable declarations require a type annotation",
//                          ident->location.line, ident->location.column_end,
//                          core::Diagnostic::Severity::Error,
//                          core::Diagnostic::Category::Parser);
//       stream.pop_restore();
//       return nullptr;
//     }

//     auto possibleParen = stream.peek(3);
//     if (possibleParen &&
//         possibleParen->descriptor->kind == core::TokenKind::LParen) {
//       stream.pop_restore();
//       return nullptr;
//     }

//     auto type = stream.peek(2);
//     if (!type || type->descriptor->group != core::TokenGroup::Type) {
//       parser.diag.report("Expected type after ':'",
//                          "Variable declarations must specify a type",
//                          colon->location.line, colon->location.column_end,
//                          core::Diagnostic::Severity::Error,
//                          core::Diagnostic::Category::Parser);
//       stream.pop_discard();
//       return nullptr;
//     }

//     auto assign = stream.peek(3);
//     if (!assign || assign->descriptor->kind != core::TokenKind::Assign) {
//       parser.diag.report("Expected '=' after type",
//                          "Variable declaration must assign a value",
//                          type->location.line, type->location.column_end,
//                          core::Diagnostic::Severity::Error,
//                          core::Diagnostic::Category::Parser);
//       stream.pop_discard();
//       return nullptr;
//     }

//     stream.advance(); // IDENT
//     stream.advance(); // :
//     stream.advance(); // TYPE
//     stream.advance(); // =

//     auto expr = parser.parse_expression(stream);
//     if (!expr) {
//       parser.diag.report("Expected expression after '='",
//                          "Variable declarations must have a value",
//                          assign->location.line, assign->location.column_end,
//                          core::Diagnostic::Severity::Error,
//                          core::Diagnostic::Category::Parser);
//       stream.pop_discard();
//       return nullptr;
//     }

//     stream.pop_discard();

//     // Retorna nó AST completo
//     return std::make_shared<VariableDeclaration>(ident->lexeme, type->lexeme,
//                                                  expr);
//   }
// };

// } // namespace interpreter::parser::plugins
