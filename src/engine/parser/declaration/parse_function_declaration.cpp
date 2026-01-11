#include "core/node/Type.hpp"
#include "engine/parser/parser.hpp"

core::node::StatementNode *Parser::parse_function_declaration() {

  if (!unit.tokens.try_match(core::token::TokenKind::FunctionKeyword)) return nullptr;

  auto *identifier = parse_identifier();

  if (!identifier) {
    synchronize_statement();
    return nullptr;
  }

  std::vector<core::node::FunctionParameterNode *> params;
  if (unit.tokens.match(core::token::TokenKind::OpenParen)) {
    while (!unit.tokens.match(core::token::TokenKind::CloseParen)) {
      auto *param_tok = unit.tokens.try_match(core::token::TokenKind::Identifier);
      if (!param_tok) return report_error(DiagnosticCode::ExpectedIdentifier, "identificador de parâmetro", unit.tokens.last_slice());

      auto *param_name = unit.ast.create_node<core::node::IdentifierNode>(unit.source.buffer.get_text(param_tok->slice.span));

      if (!unit.tokens.match(core::token::TokenKind::Colon)) return report_error(DiagnosticCode::ExpectedColon, ":", param_tok->slice);

      auto *param_type = parse_type();
      if (!param_type) return report_error(DiagnosticCode::ExpectedType, "type", param_tok->slice);

      params.push_back(unit.ast.create_node<core::node::FunctionParameterNode>(param_name, param_type, nullptr));

      unit.tokens.match(core::token::TokenKind::Comma);
    }
  }

  // --- RETORNO ---
  core::node::TypeNode *return_type = nullptr;
  if (unit.tokens.match(core::token::TokenKind::Arrow)) {
    return_type = parse_type();
    if (!return_type) return report_error(DiagnosticCode::ExpectedType, "type", unit.tokens.last_slice());
  }

  // --- BLOCO ---
  auto *body = parse_block();
  if (!body) {
    synchronize_statement();
    // body = error_recovery::make_error_node<parser::node::BlockNode>(unit);
  }

  return unit.ast.create_node<parser::node::FunctionDeclarationNode>(identifier, params, return_type, body);
}
