#pragma once
#include "core/node/Type.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include <vector>

namespace parser::statement {
inline core::node::TypeNode *parse_type(CompilationUnit &unit, core::token::TokenStream &stream) {
  stream.add_checkpoint();

  auto tok = stream.peek();
  if (!tok || tok->descriptor->kind != core::token::TokenKind::Identifier) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  auto type_name = unit.source.buffer.get_text(tok->slice.span);
  stream.advance();

  std::vector<core::node::TypeNode *> generic_args;

  tok = stream.peek();
  if (tok && tok->descriptor->kind == core::token::TokenKind::LessThan) {
    stream.advance();
    while (true) {
      auto arg = parse_type(unit, stream);
      if (!arg) { arg = unit.ast.create_node<core::node::TypeNode>("<missing>", generic_args); }
      generic_args.push_back(arg);

      tok = stream.peek();
      if (tok && tok->descriptor->kind == core::token::TokenKind::Comma) {
        stream.advance();
      } else {
        break;
      }
    }

    tok = stream.peek();
    if (!tok || tok->descriptor->kind != core::token::TokenKind::GreaterThan) {
      // Falta do '>' gera apenas um core::node::TypeNode "<missing>" no último
      // genérico
      generic_args.push_back(unit.ast.create_node<core::node::TypeNode>("<missing>", generic_args));
    } else {
      stream.advance();
    }
  }

  // Cria node de tipo sem resolver no escopo
  core::node::TypeNode *type_node = unit.ast.create_node<core::node::TypeNode>(type_name, generic_args);

  stream.discard_checkpoint();
  return type_node;
}

} // namespace parser::statement
