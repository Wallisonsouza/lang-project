
#include "core/AST.hpp"
#include "core/node/Type.hpp"
#include "parser/node/literal_nodes.hpp"
#include "parser/node/operator_nodes.hpp"
#include "parser/node/statement_nodes.hpp"

namespace optimazer {

inline core::node::ExpressionNode *
fold_constants(core::node::ExpressionNode *expr) {
  using namespace core::node;
  using namespace node;
  if (!expr)
    return nullptr;

  bool changed = true;
  while (changed) {
    changed = false;

    if (expr->kind == NodeKind::BinaryExpression) {
      auto *bin = static_cast<BinaryExpressionNode *>(expr);

      bin->left = fold_constants(bin->left);
      bin->right = fold_constants(bin->right);

      if (bin->left->kind == NodeKind::NumberLiteral &&
          bin->right->kind == NodeKind::NumberLiteral) {

        double l = static_cast<NumberLiteralNode *>(bin->left)->value;
        double r = static_cast<NumberLiteralNode *>(bin->right)->value;
        double result;

        switch (bin->op) {
        case BinaryOp::Add:
          result = l + r;
          break;
        case BinaryOp::Subtract:
          result = l - r;
          break;
        case BinaryOp::Multiply:
          result = l * r;
          break;
        case BinaryOp::Divide:
          result = l / r;
          break;
        default:
          throw std::runtime_error("Operador desconhecido");
        }

        expr = new NumberLiteralNode(result);
        changed = true; // repetir enquanto houver alterações
      }
    }
  }

  return expr;
}

inline void optimize_node(core::node::Node *node) {
  using namespace core::node;
  using namespace node;
  if (!node)
    return;

  switch (node->kind) {

  case NodeKind::BinaryExpression: {
    auto *bin = static_cast<BinaryExpressionNode *>(node);

    bin->left = fold_constants(bin->left);
    bin->right = fold_constants(bin->right);

    optimize_node(bin->left);
    optimize_node(bin->right);
    break;
  }

  case NodeKind::FunctionDeclaration: {
    auto *fn = static_cast<FunctionDeclarationNode *>(node);
    if (fn->body)
      optimize_node(fn->body);
    for (auto *param : fn->parameters)
      optimize_node(param);
    break;
  }

  case NodeKind::Block: {
    auto *block = static_cast<BlockNode *>(node);
    for (auto *stmt : block->statements)
      optimize_node(stmt);
    break;
  }

  case NodeKind::VariableDeclaration: {
    auto *var = static_cast<VariableDeclarationNode *>(node);
    if (var->value)
      var->value = fold_constants(var->value);
    break;
  }

  case NodeKind::FunctionCall: {
    auto *call = static_cast<FunctionCallNode *>(node);

    for (auto *&arg : call->args) {
      arg = fold_constants(arg);
      optimize_node(arg);
    }
    break;
  }

  case NodeKind::NumberLiteral:
  case NodeKind::StringLiteral:
  case NodeKind::Identifier:
    break;

  default:
    break;
  }
}

inline void optimize_ast(AST &ast) {
  for (auto *root : ast.get_nodes()) {
    optimize_node(root);
  }
}

} // namespace optimazer
