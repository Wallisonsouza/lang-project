// #pragma once

// #include "core/LangData.hpp"
// #include "core/parser/Node.hpp"
// #include "core/parser/ParserPlugin.hpp"
// #include "core/parser/expression/ExpressionParser.hpp"
// #include "core/token/Token.hpp"
// #include "core/utils/Stream.hpp"
// #include <memory>
// #include <vector>

// namespace interpreter::parser {

// class Parser {

// private:
//   core::LangData &data;
//   ExpressionParser expr_parser;

// public:
//   std::vector<std::shared_ptr<ParserPlugin>> statement_plugins;
//   std::vector<std::shared_ptr<ExpressionPlugin>> expression_plugins;

//   const core::LangData &get_data() { return data; }

//   Parser(core::LangData &data)
//       : expr_parser(data, expression_plugins), data(data) {}

//   std::shared_ptr<Node> run(core::Stream<core::Token> &stream) {
//     for (auto &p : statement_plugins) {
//       if (auto node = p->match(*this, stream))
//         return node;
//     }
//     return nullptr;
//   }

//   std::shared_ptr<ExpressionNode>
//   parse_expression(core::Stream<core::Token> &stream) {
//     return expr_parser.parse(stream);
//   }

//   std::vector<std::shared_ptr<Node>>
//   generate_ast(std::vector<std::shared_ptr<core::Token>> &tokens) {

//     core::Stream<core::Token> stream(tokens);
//     std::vector<std::shared_ptr<Node>> result;

//     while (!stream.eof()) {
//       auto node = run(stream);

//       if (node) {
//         result.push_back(node);
//       } else {
//         stream.advance();
//       }
//     }

//     return result;
//   }
// };

// } // namespace interpreter::parser
