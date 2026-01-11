#include "engine/parser/parser.hpp"

core::node::IdentifierNode *Parser::parse_identifier() {
  auto *tok = unit.tokens.try_match(core::token::TokenKind::Identifier);

  if (!tok) {
    report_error(DiagnosticCode::ExpectedIdentifier, "identificador", unit.tokens.last_slice());
    return nullptr;
  }

  return unit.ast.create_node<core::node::IdentifierNode>(unit.source.buffer.get_text(tok->slice.span), tok->slice);
}
