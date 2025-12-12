// #pragma once

// #include "core/parser/Parser.hpp"
// #include "core/parser/expression/ExpressionPlugin.hpp"
// #include "core/token/TokenKind.hpp"

// namespace interpreter::parser {

// class ParenthesesExpressionPlugin : public ExpressionPlugin {
// public:
//   std::shared_ptr<ExpressionNode> match(core::Stream<core::Token> &stream,
//                                         ExpressionParser &parser) override {

//     auto open = stream.peek();
//     if (!open || open->descriptor->kind != core::TokenKind::LParen)
//       return nullptr;

//     stream.advance();

//     std::shared_ptr<ExpressionNode> expr = parser.parse(stream);
//     if (!expr)
//       return nullptr;

//     auto close = stream.peek();
//     if (!close || close->descriptor->kind != core::TokenKind::RParen)
//       return nullptr;

//     stream.advance();

//     return expr;
//   }
// };

// } // namespace interpreter::parser
