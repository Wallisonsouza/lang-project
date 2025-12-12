// #pragma once
// #include "core/LangData.hpp"
// #include "core/parser/Node.hpp"
// #include "core/parser/expression/ExpressionPlugin.hpp"
// #include "core/token/Token.hpp"
// #include "core/utils/Stream.hpp"
// #include <memory>
// #include <vector>

// namespace interpreter::parser {

// class ExpressionParser {

// private:
//   const core::LangData &data;
//   std::vector<std::shared_ptr<ExpressionPlugin>> &plugins;

// public:
//   const core::LangData &get_data() { return data; }

//   ExpressionParser(const core::LangData &data,
//                    std::vector<std::shared_ptr<ExpressionPlugin>> &plugins)
//       : data(data), plugins(plugins) {}

//   std::shared_ptr<ExpressionNode> parse(core::Stream<core::Token> &stream) {
//     return parse_binary(stream, 0);
//   }

//   std::shared_ptr<ExpressionNode>
//   parse_primary(core::Stream<core::Token> &stream) {
//     for (auto &p : plugins) {
//       if (auto expr = p->match(stream, *this))
//         return expr;
//     }
//     return nullptr;
//   }

//   std::shared_ptr<ExpressionNode>
//   parse_binary(core::Stream<core::Token> &stream, int parent_prec) {
//     auto left = parse_primary(stream);
//     if (!left)
//       return nullptr;

//     while (true) {
//       auto tok = stream.peek();
//       if (!tok)
//         break;

//       int prec = data.precedence_table.get_precedence(tok->descriptor->kind);
//       if (prec < parent_prec)
//         break;

//       bool right_assoc =
//           data.precedence_table.is_right_associative(tok->descriptor->kind);

//       stream.advance();

//       int next_min_prec = right_assoc ? prec : prec + 1;

//       auto right = parse_binary(stream, next_min_prec);
//       if (!right)
//         return nullptr;

//       left = std::make_shared<BinaryExpression>(
//           left, data.buffer.get_text(tok->span), right);
//     }

//     return left;
//   }
// };

// } // namespace interpreter::parser
