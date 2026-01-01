#pragma once

#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/statement/parse_statement.hpp"

namespace parser {

class Parser {
public:
  void generate_ast(CompilationUnit &unit) {

    auto &stream = unit.tokens;

    while (!stream.is_end()) {
      auto node = parse_node(unit, stream);
      if (node) {
        unit.ast.add_root(node);
      } else {
        stream.advance();
      }
    }
  }

private:
  core::node::Node *parse_node(CompilationUnit &unit, core::token::TokenStream &stream) { return parser::statement::parse_statement(unit, stream); }
};

} // namespace parser
