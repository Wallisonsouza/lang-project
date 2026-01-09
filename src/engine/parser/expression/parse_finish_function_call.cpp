#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

core::node::ExpressionNode *
Parser::finish_call(core::node::ExpressionNode *base) {
  if (!base)
    return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok || tok->descriptor->kind != core::token::TokenKind::OpenParen)
      break;
    unit.tokens.advance(); // consumir '('

    std::vector<core::node::ExpressionNode *> args;
    while (!unit.tokens.is_end() &&
           !unit.tokens.match(core::token::TokenKind::CloseParen)) {
      auto *expr = parse_expression();
      if (!expr)
        break;
      args.push_back(expr);

      if (!unit.tokens.match(core::token::TokenKind::Comma)) {
        unit.tokens.match(core::token::TokenKind::CloseParen);
        break;
      }
    }

    base = unit.ast.create_node<parser::node::FunctionCallNode>(base, args);
  }

  return base;
}
