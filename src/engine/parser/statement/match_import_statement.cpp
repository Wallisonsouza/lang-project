#include "core/node/Type.hpp"
#include "core/token/Location.hpp"
#include "core/token/TokenKind.hpp"
#include "core/token/token_stream.hpp"
#include "diagnostic/Diagnostic.hpp"
#include "engine/CompilationUnit.hpp"

#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/parser.hpp"
#include <optional>
#include <string>
#include <vector>

core::node::StatementNode *Parser::parse_import_statement() {

  if (!unit.tokens.try_match(core::token::TokenKind::UseKeyword)) return nullptr;

  std::vector<parser::node::IdentifierNode *> path_nodes;

  while (true) {
    auto name_token = unit.tokens.try_match(core::token::TokenKind::Identifier);
    if (!name_token) {

      report_error(DiagnosticCode::ExpectedToken, unit.tokens.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::Identifier, .found = unit.tokens.peek()});
      break;
    };

    auto name = unit.source.buffer.get_text(name_token->slice.span);
    auto *id_node = unit.ast.create_node<parser::node::IdentifierNode>(name);
    path_nodes.push_back(id_node);

    auto next = unit.tokens.peek();
    if (!next) break;

    if (unit.tokens.try_match(core::token::TokenKind::DoubleColon)) continue;

    report_error(DiagnosticCode::ExpectedToken, unit.tokens.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::DoubleColon, .found = unit.tokens.peek()});

    unit.tokens.advance();
  }

  if (path_nodes.empty()) return nullptr;

  std::optional<std::string> alias;
  auto as_tok = unit.tokens.peek();
  if (as_tok && as_tok->descriptor->kind == core::token::TokenKind::AsKeyword) {
    unit.tokens.advance();
    auto id_tok = unit.tokens.peek();
    if (!id_tok || id_tok->descriptor->kind != core::token::TokenKind::Identifier) {
      // unit.diagnostics.emit(DiagnosticCode::ExpectedToken, core::token::TokenKind::AsKeyword, id_tok);
      return nullptr;
    }
    alias = unit.source.buffer.get_text(id_tok->slice.span);
    unit.tokens.advance();
  }

  auto *node = unit.ast.create_node<parser::node::statement::ImportNode>(std::move(path_nodes));
  node->alias = std::move(alias);
  node->slice = unit.tokens.last_slice();
  return node;
}
