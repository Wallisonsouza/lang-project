#include "parse_expression.hpp"
#include "engine/parser/expression/parse_function_expression.hpp"
#include "engine/parser/expression/parse_index_access.hpp"
#include "parse_binary_expression.hpp"
#include "parse_member_access.hpp"
#include "parse_primary_expression.hpp"
namespace parser::expression {

core::node::ExpressionNode *parse_expression(CompilationUnit &unit, core::token::TokenStream &stream) {

  auto *base = parse_primary_expression(unit, stream);
  if (!base) return nullptr;

  while (true) {
    auto *tok = stream.peek();
    if (!tok) break;

    if (tok->descriptor->kind == core::token::TokenKind::Dot) {
      base = parse_member_access(unit, stream, base);
    } else if (tok->descriptor->kind == core::token::TokenKind::OpenParen) {
      base = parse_function_expression(unit, stream, base);
    } else if (tok->descriptor->kind == core::token::TokenKind::OpenBracket) {
      base = parse_index_access(unit, stream, base);
    } else {
      break;
    }
  }

  base = parse_binary_expression(unit, stream, 0, base);

  return base;
}

} // namespace parser::expression
