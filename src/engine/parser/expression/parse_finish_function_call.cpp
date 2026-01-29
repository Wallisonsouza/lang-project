#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

core::ast::ASTExpressionNode *Parser::finish_call(core::ast::ASTExpressionNode *base) {
  if (!base) return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok || tok->descriptor->kind != TokenKind::OpenParen) break;
    unit.tokens.advance(); // consumir '('

    std::vector<core::ast::ASTExpressionNode *> args;
    while (!unit.tokens.is_end() && !unit.tokens.match(TokenKind::CloseParen)) {
      auto *expr = parse_expression();
      if (!expr) break;
      args.push_back(expr);

      if (!unit.tokens.match(TokenKind::COMMA)) {
        unit.tokens.match(TokenKind::CloseParen);
        break;
      }
    }

    base = unit.ast.create_node<parser::node::FunctionCallNode>(base, args);
  }

  return base;
}
