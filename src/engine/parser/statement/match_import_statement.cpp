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

  if (!stream.try_match(core::token::TokenKind::UseKeyword)) return nullptr;

  std::vector<parser::node::IdentifierNode *> path_nodes;

  while (true) {
    auto name_token = stream.try_match(core::token::TokenKind::Identifier);
    if (!name_token) {

      report_error(DiagnosticCode::ExpectedToken, stream.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::Identifier, .found = stream.peek()});
      break;
    };

    auto name = unit.source.buffer.get_text(name_token->slice.span);
    auto *id_node = unit.ast.create_node<parser::node::IdentifierNode>(name);
    path_nodes.push_back(id_node);

    auto next = stream.peek();
    if (!next) break;

    if (stream.try_match(core::token::TokenKind::DoubleColon)) continue;

    report_error(DiagnosticCode::ExpectedToken, stream.last_slice(), DiagnosticToken{.expected = core::token::TokenKind::DoubleColon, .found = stream.peek()});

    stream.advance();
  }

  if (path_nodes.empty()) return nullptr;

  std::optional<std::string> alias;
  auto as_tok = stream.peek();
  if (as_tok && as_tok->descriptor->kind == core::token::TokenKind::AsKeyword) {
    stream.advance();
    auto id_tok = stream.peek();
    if (!id_tok || id_tok->descriptor->kind != core::token::TokenKind::Identifier) {
      // unit.diagnostics.emit(DiagnosticCode::ExpectedToken, core::token::TokenKind::AsKeyword, id_tok);
      return nullptr;
    }
    alias = unit.source.buffer.get_text(id_tok->slice.span);
    stream.advance();
  }

  auto *node = unit.ast.create_node<parser::node::statement::ImportNode>(std::move(path_nodes));
  node->alias = std::move(alias);
  node->slice = stream.last_slice();
  return node;
}
