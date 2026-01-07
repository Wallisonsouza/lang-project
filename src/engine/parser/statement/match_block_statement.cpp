#include "core/token/TokenKind.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "engine/parser/parser.hpp"

parser::node::BlockNode *Parser::parse_block() {

  auto tok = stream.peek();

  if (!tok && tok->descriptor->kind != core::token::TokenKind::OpenBrace) { return nullptr; }

  stream.consume();

  std::vector<core::node::StatementNode *> statements;

  while (!stream.is_end()) {

    auto tok = stream.peek();

    if (tok && tok->descriptor->kind == core::token::TokenKind::CloseBrace) {
      stream.advance();
      return unit.ast.create_node<parser::node::BlockNode>(std::move(statements));
    }

    auto stmt = parse_statement();

    if (!stmt) { return unit.ast.create_node<parser::node::BlockNode>(std::move(statements)); }

    statements.push_back(stmt);
  }

  return unit.ast.create_node<parser::node::BlockNode>(std::move(statements));
}
