#include "core/node/Type.hpp"
#include "core/node/flags.hpp"
#include "engine/parser/parser.hpp"

core::node::ParameterListNode *
Parser::parse_list(TokenKind open_token, TokenKind close_token,
                   TokenKind separator_token,
                   std::function<core::node::PatternNode *()> parse_element) {

  std::vector<core::node::PatternNode *> elements;

  if (!unit.tokens.match(open_token)) {
    auto desc = unit.context.descriptor_table.lookup_by_kind(open_token);
    report_error(DiagnosticCode::ExpectedToken,
                 desc ? desc->name : "opening token");
    return unit.ast.create_node<core::node::ParameterListNodeError>(
        unit.tokens.last_slice());
  }

  bool expect_element = true;

  while (!unit.tokens.is_end()) {
    consume_statement_separators();

    if (unit.tokens.match(close_token)) {
      return unit.ast.create_node<core::node::ParameterListNode>(
          std::move(elements));
    }

    auto *current = unit.tokens.peek();
    if (!current)
      break;

    if (expect_element) {
      auto *el = parse_element();

      // Fail-fast: se o elemento tem erro, apenas retorna nó de erro
      if (!el || el->flags.has(NodeFlags::HasError)) {
        return unit.ast.create_node<core::node::ParameterListNodeError>(
            unit.tokens.last_slice());
      }

      elements.push_back(el);
      expect_element = false;
      continue;
    }

    // Esperando ',' ou ')'
    if (unit.tokens.match(separator_token)) {
      expect_element = true;
      continue;
    }

    // Se não for ',' nem ')', é erro
    if (current->descriptor->kind == TokenKind::OpenBrace) {
      report_error(DiagnosticCode::ExpectedToken,
                   "expected ')' before function body");
    } else {
      auto sep_desc =
          unit.context.descriptor_table.lookup_by_kind(separator_token);
      report_error(DiagnosticCode::ExpectedToken,
                   sep_desc ? sep_desc->name : "separator between parameters");
    }

    return unit.ast.create_node<core::node::ParameterListNodeError>(
        unit.tokens.last_slice());
  }

  report_error(DiagnosticCode::ExpectedToken,
               "unterminated parameter list, missing ')'");
  return unit.ast.create_node<core::node::ParameterListNodeError>(
      unit.tokens.last_slice());
}
