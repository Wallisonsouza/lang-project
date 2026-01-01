#include "core/node/BinaryOp.hpp"
#include "engine/parser/expression/parse_expression.hpp"
#include "engine/parser/node/operator_nodes.hpp"

namespace parser::expression {

core::node::ExpressionNode *parse_binary_expression(CompilationUnit &unit, core::token::TokenStream &stream, int min_precedence, core::node::ExpressionNode *lhs) {

  auto *left = lhs ? lhs : parse_expression(unit, stream);
  if (!left) return nullptr;

  while (true) {
    auto *tok = stream.peek();
    if (!tok) break;

    int prec = unit.context.precedence_table.get_precedence(tok->descriptor->kind);
    if (prec < min_precedence) break;

    bool right_assoc = unit.context.precedence_table.is_right_associative(tok->descriptor->kind);
    stream.advance();

    int next_min_prec = right_assoc ? prec : prec + 1;

    auto *right = parse_binary_expression(unit, stream, next_min_prec, nullptr);
    if (!right) return nullptr;

    core::node::BinaryOperation op;

    switch (tok->descriptor->kind) {
    case core::token::TokenKind::Plus: op = core::node::BinaryOperation::Add; break;
    case core::token::TokenKind::Minus: op = core::node::BinaryOperation::Subtract; break;
    case core::token::TokenKind::Star: op = core::node::BinaryOperation::Multiply; break;
    case core::token::TokenKind::Slash: op = core::node::BinaryOperation::Divide; break;
    default: return left;
    }

    left = unit.ast.create_node<node::BinaryExpressionNode>(left, op, right);
  }

  return left;
}

} // namespace parser::expression
