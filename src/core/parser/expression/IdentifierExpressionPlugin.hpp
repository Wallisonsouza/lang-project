// #pragma once
// #include "core/parser/Node.hpp"
// #include "core/parser/expression/ExpressionParser.hpp"
// #include "core/parser/expression/ExpressionPlugin.hpp"

// class IdentifierExpressionPlugin : public interpreter::parser::ExpressionPlugin {
// public:
//   std::shared_ptr<interpreter::parser::ExpressionNode> match(interpreter::core::Stream<interpreter::core::Token> &stream, interpreter::parser::ExpressionParser &parser) override {

//     auto tok = stream.peek();
//     if (!tok) return nullptr;

//     if (tok->descriptor->kind != interpreter::core::TokenKind::Identifier) return nullptr;

//     const auto &data = parser.get_data();

//     stream.advance();

//     auto name = data.buffer.get_text(tok->span);

//     return std::make_shared<interpreter::parser::IdentifierNode>(std::move(name));
//   }
// };
