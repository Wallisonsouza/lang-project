#include "engine/CompilationUnit.hpp"
#include "engine/parser/expression/parse_primary_expression.hpp"
#include "engine/parser/node/statement_nodes.hpp"

namespace parser::expression {

inline core::node::ExpressionNode *parse_member_access(CompilationUnit &unit, core::token::TokenStream &stream, core::node::ExpressionNode *base) {
  if (!base) return nullptr;

  while (true) {
    auto *dot = stream.peek();
    if (!dot || dot->descriptor->kind != core::token::TokenKind::Dot) break;
    stream.advance();

    auto *prop_expr = parse_primary_expression(unit, stream);
    if (!prop_expr) break;

    base = unit.ast.create_node<node::MemberAccessNode>(base, prop_expr);
  }

  return base;
}

} // namespace parser::expression
