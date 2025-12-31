#pragma once

#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/declaration/parse_variable_declaration.hpp"

namespace parser {

class Parser {
public:
  void generate_ast(CompilationUnit &unit) {

    auto &stream = unit.tokens;

    while (!stream.is_end()) {
      auto node = match_node(unit, stream);
      if (node) {
        unit.ast.add_root(node);
      } else {
        stream.advance();
      }
    }
  }

private:
  core::node::Node *match_node(CompilationUnit &unit, core::token::TokenStream &stream) {

    // if (auto n = parser::match::match_import_statement(unit, stream)) return n;
    if (auto n = parser::declaration::parse_variable_declaration(unit, stream)) return n;
    // if (auto n = parser::match::match_function_declaration(unit, stream)) return n;
    // if (auto n = parser::match::match_function_call(unit, stream)) return n;
    // if (auto n = parser::match::parse_callee(unit, stream)) return n;

    return nullptr;
  }
};

} // namespace parser
