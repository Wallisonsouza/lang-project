#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_import_statement() {
  if (!unit.tokens.match(core::token::TokenKind::IMPORT_KEYWORD))
    return nullptr;

  std::vector<core::node::IdentifierNode *> path_nodes;

  // primeiro identificador é obrigatório
  auto *name_token = unit.tokens.match(core::token::TokenKind::Identifier);
  if (!name_token) {
    report_error(DiagnosticCode::ExpectedToken,
                 "expected module name after 'import'",
                 unit.tokens.peek_slice());
    return nullptr;
  }

  while (true) {
    auto name = unit.source.buffer.get_text(name_token->slice.span);
    path_nodes.push_back(
        unit.ast.create_node<core::node::IdentifierNode>(name));

    if (!unit.tokens.match(core::token::TokenKind::Dot))
      break;

    name_token = unit.tokens.match(core::token::TokenKind::Identifier);
    if (!name_token) {
      report_error(DiagnosticCode::ExpectedToken,
                   "expected identifier after '.' in import path",
                   unit.tokens.peek_slice());
      break;
    }
  }

  // std::optional<std::string> alias;
  // if (unit.tokens.match(core::token::TokenKind::AsKeyword)) {
  //   auto *id_tok = unit.tokens.match(core::token::TokenKind::Identifier);
  //   if (!id_tok) {
  //     report_error(DiagnosticCode::ExpectedToken,
  //                  "expected identifier after 'as'",
  //                  unit.tokens.peek_slice());
  //   } else {
  //     alias = unit.source.buffer.get_text(id_tok->slice.span);
  //   }
  // }

  auto *node = unit.ast.create_node<parser::node::statement::ImportNode>(
      std::move(path_nodes));
  node->slice = unit.tokens.last_slice();
  return node;
}
