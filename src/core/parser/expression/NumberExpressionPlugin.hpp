// #pragma once
// #include "core/parser/expression/ExpressionPlugin.hpp"

// class NumberExpressionPlugin : public interpreter::parser::ExpressionPlugin {
// public:
//   std::shared_ptr<interpreter::parser::ExpressionNode> match(interpreter::core::Stream<interpreter::core::Token> &stream, interpreter::parser::ExpressionParser &) override {

//     auto tok = stream.peek();
//     if (!tok || tok->descriptor->kind != interpreter::core::TokenKind::Number) return nullptr;

//     double value = std::stod(std::string(tok->lexeme.begin(), tok->lexeme.end()));
//     stream.advance();

//     return std::make_shared<interpreter::parser::NumberLiteralNode>(value);
//   }
// };
