#include "core/module/scope.hpp"
#include "core/node/BinaryOp.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <iostream>
#include <vector>

inline parser::node::NumberLiteralNode *
number_operations(parser::node::NumberLiteralNode *lhs,
                  core::node::BinaryOperation op,
                  parser::node::NumberLiteralNode *rhs) {

  switch (op) {
  case core::node::BinaryOperation::Add:
    return new parser::node::NumberLiteralNode(lhs->value + rhs->value);

  case core::node::BinaryOperation::Subtract:
    return new parser::node::NumberLiteralNode(lhs->value - rhs->value);

  case core::node::BinaryOperation::Divide:
    return new parser::node::NumberLiteralNode(lhs->value / rhs->value);

  case core::node::BinaryOperation::Multiply:
    return new parser::node::NumberLiteralNode(lhs->value * rhs->value);

  default:
    return nullptr;
  }
}

struct Executor {
  core::Scope *current_scope;

  Executor(core::Scope *scope) : current_scope(scope) {}

  core::node::Node *
  execute_binary_expression(parser::node::BinaryExpressionNode *node) {

    auto *lhs = execute(node->left);
    auto *rhs = execute(node->right);

    if (!lhs || !rhs) {
      return nullptr;
    }

    if (lhs->kind == core::node::NodeKind::NumberLiteral &&
        rhs->kind == core::node::NodeKind::NumberLiteral) {

      return number_operations(
          static_cast<parser::node::NumberLiteralNode *>(lhs), node->op,
          static_cast<parser::node::NumberLiteralNode *>(rhs));
    }

    std::cerr << "[Executor] Operação binária inválida para os tipos dados.\n";
    return nullptr;
  }

  core::node::Node *
  execute_path_expression(parser::node::statement::PathExprNode *node) {
    return node->resolved_symbol ? node->resolved_symbol->declaration : nullptr;
  }

  core::node::Node *
  execute_function_expression(parser::node::FunctionCallNode *node) {
    auto *callee_node = execute(node->callee);
    if (!callee_node)
      return nullptr;

    if (callee_node->kind == core::node::NodeKind::NativeFunctionDeclaration) {
      auto *native =
          static_cast<core::node::NativeFunctionDeclarationNode *>(callee_node);

      std::vector<core::node::Node *> args_values;
      for (auto *arg : node->args) {
        args_values.push_back(execute(arg));
      }

      return native->callback(args_values);
    }

    return nullptr;
  }

  core::node::Node *execute(core::node::Node *node) {
    if (!node)
      return nullptr;

    switch (node->kind) {
    case core::node::NodeKind::BinaryExpression:
      return execute_binary_expression(
          static_cast<parser::node::BinaryExpressionNode *>(node));

    case core::node::NodeKind::PathExpr:
      return execute_path_expression(
          static_cast<parser::node::statement::PathExprNode *>(node));

    case core::node::NodeKind::FunctionCall:
      return execute_function_expression(
          static_cast<parser::node::FunctionCallNode *>(node));

    case core::node::NodeKind::NumberLiteral:
    case core::node::NodeKind::StringLiteral:
      return node;

    case core::node::NodeKind::Import:
      return nullptr;

    default:
      return nullptr;
    }
  }
};
