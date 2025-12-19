#pragma once

#include "core/CompilationUnit.hpp"
#include "core/token/Token.hpp"
#include "parser/ExpressionParser.hpp"
#include "parser/match/match_function_declaration.hpp"
#include "parser/match/match_type_declaration.hpp"
#include "parser/match/match_variable_declaration.hpp"
#include "utils/Stream.hpp"

namespace parser {

class Parser {
public:
  void generate_ast(CompilationUnit &unit) {
    utils::Stream<core::token::Token *> stream(unit.tokens.get_tokens());

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
  ExpressionParser exp_engine;

  core::node::Node *match_node(CompilationUnit &unit, utils::Stream<core::token::Token *> &stream) {
    if (auto n = parser::match::match_variable_declaration(unit, stream, exp_engine)) return n;
    if (auto n = parser::match::match_function_declaration(unit, stream, exp_engine)) return n;

    // futuras regras de parsing: funções, structs, etc.
    return nullptr;
  }
};

} // namespace parser
