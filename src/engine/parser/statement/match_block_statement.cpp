#include "core/token/TokenKind.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

parser::node::BlockNode *Parser::parse_block() {

  auto tok = unit.tokens.peek();

  if (!tok && tok->descriptor->kind != core::token::TokenKind::OpenBrace) { return nullptr; }

  unit.tokens.consume();

  std::vector<core::node::StatementNode *> statements;

  while (!unit.tokens.is_end()) {

    auto tok = unit.tokens.peek();

    if (tok && tok->descriptor->kind == core::token::TokenKind::CloseBrace) {
      unit.tokens.advance();
      return unit.ast.create_node<parser::node::BlockNode>(std::move(statements));
    }

    auto stmt = parse_statement();

    if (!stmt) { return unit.ast.create_node<parser::node::BlockNode>(std::move(statements)); }

    statements.push_back(stmt);
  }

  return unit.ast.create_node<parser::node::BlockNode>(std::move(statements));
}
