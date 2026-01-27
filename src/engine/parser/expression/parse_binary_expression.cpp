#include "core/node/BinaryOp.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/parser.hpp"

core::node::ExpressionNode *
Parser::parse_binary_expression(int min_precedence,
                                core::node::ExpressionNode *left) {
  if (!left)
    return nullptr;

  while (true) {
    auto *tok = unit.tokens.peek();
    if (!tok)
      break;

    int prec =
        unit.context.precedence_table.get_precedence(tok->descriptor->kind);
    if (prec < min_precedence)
      break;

    bool right_assoc = unit.context.precedence_table.is_right_associative(
        tok->descriptor->kind);

    unit.tokens.advance();

    auto *right = parse_primary_expression();
    if (!right)
      return nullptr;

    int next_min_prec = right_assoc ? prec : prec + 1;

    while (true) {
      auto *next = unit.tokens.peek();
      if (!next)
        break;

      int next_prec =
          unit.context.precedence_table.get_precedence(next->descriptor->kind);

      if (next_prec < next_min_prec)
        break;

      right = parse_binary_expression(next_min_prec, right);
    }

    core::node::BinaryOperation op;
    switch (tok->descriptor->kind) {
    case TokenKind::Plus:
      op = core::node::BinaryOperation::Add;
      break;
    case TokenKind::Minus:
      op = core::node::BinaryOperation::Subtract;
      break;
    case TokenKind::Star:
      op = core::node::BinaryOperation::Multiply;
      break;
    case TokenKind::Slash:
      op = core::node::BinaryOperation::Divide;
      break;
    case TokenKind::Equals:
      op = core::node::BinaryOperation::Equal;
      break;
    case TokenKind::LessThan:
      op = core::node::BinaryOperation::Less;
      break;
    default:
      return left;
    }

    left = unit.ast.create_node<parser::node::BinaryExpressionNode>(left, op,
                                                                    right);
  }

  return left;
}
