#include "core/node/Type.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/parser.hpp"

#include <vector>

core::node::TypeNode *Parser::parse_type() {

  auto name_token = unit.tokens.match(core::token::TokenKind::Identifier);
  if (!name_token) { return nullptr; }

  auto type_name = unit.source.buffer.get_text(name_token->slice.span);

  auto id = unit.ast.create_node<core::node::IdentifierNode>(type_name);

  std::vector<core::node::TypeNode *> generic_args;

  // tok = unit.tokens.peek();
  // if (tok && tok->descriptor->kind == core::token::TokenKind::LessThan) {
  //   unit.tokens.advance();
  //   while (true) {
  //     auto arg = parse_type();
  //     if (!arg) { arg = unit.ast.create_node<core::node::TypeNode>("<missing>", generic_args); }
  //     generic_args.push_back(arg);

  //     tok = unit.tokens.peek();
  //     if (tok && tok->descriptor->kind == core::token::TokenKind::Comma) {
  //       unit.tokens.advance();
  //     } else {
  //       break;
  //     }
  //   }

  //   tok = unit.tokens.peek();s
  //   if (!tok || tok->descriptor->kind != core::token::TokenKind::GreaterThan) {
  //     // Falta do '>' gera apenas um core::node::TypeNode "<missing>" no último
  //     // genérico
  //     generic_args.push_back(unit.ast.create_node<core::node::TypeNode>("<missing>", generic_args));
  //   } else {
  //     unit.tokens.advance();
  //   }
  // }

  // Cria node de tipo sem name_resolution no escopo

  return unit.ast.create_node<core::node::TypeNode>(id, generic_args);
}
