#include "parse_primary_expression.hpp"
#include "engine/parser/expression/parse_expression.hpp"
#include "engine/parser/expression/parse_path_expression.hpp"
#include "engine/parser/node/literal_nodes.hpp"

namespace parser::expression {

core::node::ExpressionNode *
parse_primary_expression(CompilationUnit &unit,
                         core::token::TokenStream &stream) {

  auto *tok = stream.peek();
  if (!tok)
    return nullptr;

  core::node::ExpressionNode *result = nullptr;

  // -------- núcleo --------
  switch (tok->descriptor->kind) {

  case core::token::TokenKind::NumberLiteral: {
    result = unit.ast.create_node<node::NumberLiteralNode>(
        std::stod(unit.source.buffer.get_text(tok->slice.span)));
    stream.advance();
    break;
  }

  case core::token::TokenKind::StringLiteral: {
    result = unit.ast.create_node<parser::node::StringLiteralNode>(
        unit.source.buffer.get_text(tok->slice.span));
    stream.advance();
    break;
  }

  case core::token::TokenKind::Identifier: {
    auto *next = stream.peek(1);
    if (next && next->descriptor->kind == core::token::TokenKind::DoubleColon) {
      result = parse_path(unit, stream);
    } else {
      result = unit.ast.create_node<parser::node::IdentifierNode>(
          unit.source.buffer.get_text(tok->slice.span));
      result->slice = tok->slice;
      stream.advance();
    }
    break;
  }

  case core::token::TokenKind::OpenParen: {
    stream.advance();
    result = parse_expression(unit, stream);
    auto *close = stream.consume();
    if (!result || !close ||
        close->descriptor->kind != core::token::TokenKind::CloseParen)
      return nullptr;
    break;
  }

  default:
    return nullptr;
  }

  return result;
}

} // namespace parser::expression
