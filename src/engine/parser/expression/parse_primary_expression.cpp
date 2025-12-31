#include "parse_primary_expression.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "parse_binary_expression.hpp"
#include "utils/Utf8.hpp"

namespace parser::expression {

core::node::ExpressionNode *parse_primary_expression(CompilationUnit &unit, core::token::TokenStream &stream) {

  stream.add_checkpoint();
  auto *tok = stream.consume();

  if (!tok || !tok->descriptor) {
    stream.rollback_checkpoint();
    return nullptr;
  }

  core::node::ExpressionNode *result = nullptr;

  switch (tok->descriptor->kind) {

  case core::token::TokenKind::NumberLiteral: {
    auto text = unit.source.buffer.get_text(tok->slice.span);
    double value = std::stod(utils::Utf::utf32to8(text));
    result = unit.ast.create_node<node::NumberLiteralNode>(value);
    break;
  }

  case core::token::TokenKind::StringLiteral: {
    auto text = unit.source.buffer.get_text(tok->slice.span);
    result = unit.ast.create_node<parser::node::StringLiteralNode>(text);
    break;
  }

  case core::token::TokenKind::Identifier: {
    auto name = unit.source.buffer.get_text(tok->slice.span);
    result = unit.ast.create_node<parser::node::IdentifierNode>(name);
    break;
  }

  case core::token::TokenKind::OpenParen: {
    result = parse_binary_expression(unit, stream, 0);

    auto *close = stream.consume();
    if (!result || !close || close->descriptor->kind != core::token::TokenKind::CloseParen) {
      stream.rollback_checkpoint();
      return nullptr;
    }
    break;
  }

  default: stream.rollback_checkpoint(); return nullptr;
  }

  stream.discard_checkpoint();
  return result;
}

} // namespace parser::expression
