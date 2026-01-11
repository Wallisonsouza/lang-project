#pragma once
#include "core/memory/symbol.hpp"
#include "core/node/BinaryOp.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "engine/CompilationUnit.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include "runtime_scope.hpp"

struct Executor {

  RuntimeScope *current_scope;

  Executor(RuntimeScope *scope) : current_scope(scope) {}

  Value execute_assignment(CompilationUnit &unit, parser::node::statement::AssignmentNode *node) {
    // 1. Executa o valor da atribuição
    Value val = execute_node(unit, node->value);

    if (auto *id = dynamic_cast<core::node::IdentifierNode *>(node->target)) {
      current_scope->set(id->symbol_id, val);
    } else {
      throw std::runtime_error("Invalid assignment target");
    }

    return val; // ou Void()
  }

  Value execute_node(CompilationUnit &unit, core::node::Node *node) {
    if (!node) return Value::Null();

    switch (node->kind) {

    case core::node::NodeKind::ExpressionStatement: {
      auto *es = static_cast<core::node::ExpressionStatementNode *>(node);
      execute_node(unit, es->expr);
      return Value::Void();
    }

    case core::node::NodeKind::Assignment: {
      return execute_assignment(unit, static_cast<parser::node::statement::AssignmentNode *>(node));
    }

    case core::node::NodeKind::Identifier: return execute_identifier(static_cast<core::node::IdentifierNode *>(node)->symbol_id);

    case core::node::NodeKind::NumberLiteral: return Value::Number(static_cast<parser::node::NumberLiteralNode *>(node)->value);

    case core::node::NodeKind::StringLiteral: return Value::String(static_cast<parser::node::StringLiteralNode *>(node)->value);

    case core::node::NodeKind::BinaryExpression: return execute_binary(unit, static_cast<parser::node::BinaryExpressionNode *>(node));

    case core::node::NodeKind::PathExpression: return execute_identifier(static_cast<parser::node::statement::PathExprNode *>(node)->symbol_id);

    case core::node::NodeKind::FunctionCall: return execute_function(unit, static_cast<parser::node::FunctionCallNode *>(node));

    case core::node::NodeKind::VariableDeclaration: return execute_variable_declaration(unit, static_cast<parser::node::VariableDeclarationNode *>(node));

    case core::node::NodeKind::Block: return execute_block(unit, static_cast<parser::node::BlockNode *>(node));

    case core::node::NodeKind::IfStatement: return execute_if(unit, static_cast<parser::node::IfStatementNode *>(node));

    default: return Value::Null();
    }
  }

  Value execute_block(CompilationUnit &unit, parser::node::BlockNode *block) {
    if (!block) return Value::Void();

    Value last_value = Value::Void();
    for (auto *stmt : block->statements) { last_value = execute_node(unit, stmt); }

    return last_value;
  }

  Value execute_if(CompilationUnit &unit, parser::node::IfStatementNode *node) {

    if (!node || !node->condition) return Value::Void();

    Value cond = execute_node(unit, node->condition);
    bool cond_truthy = cond.as_bool();

    if (cond_truthy) {
      return execute_block(unit, node->then_block);
    } else {
      return execute_block(unit, node->else_block);
    }
  }

  Value execute_identifier(SymbolId id) {
    if (id == INVALID_SYMBOL_ID) return Value::Null();
    return current_scope->get(id);
  }

  Value execute_binary(CompilationUnit &unit, parser::node::BinaryExpressionNode *node) {
    Value lhs = execute_node(unit, node->left);
    Value rhs = execute_node(unit, node->right);

    switch (node->op) {
    case core::node::BinaryOperation::Add: return Value::Number(lhs.get_number() + rhs.get_number());
    case core::node::BinaryOperation::Subtract: return Value::Number(lhs.get_number() - rhs.get_number());
    case core::node::BinaryOperation::Multiply: return Value::Number(lhs.get_number() * rhs.get_number());
    case core::node::BinaryOperation::Divide: return Value::Number(lhs.get_number() / rhs.get_number());
    case core::node::BinaryOperation::Equal: return Value::Boolean(lhs.get_number() == rhs.get_number());
    case core::node::BinaryOperation::Less: return Value::Boolean(lhs.get_number() < rhs.get_number());
    default: return Value::Null();
    }
  }

  Value execute_variable_declaration(CompilationUnit &unit, parser::node::VariableDeclarationNode *node) {

    Value value = Value::Null();

    if (node->value) { value = execute_node(unit, node->value); }

    if (node->symbol_id == INVALID_SYMBOL_ID) { throw std::runtime_error("Variable declaration has invalid symbol id"); }

    current_scope->set(node->symbol_id, value);

    return Value::Void();
  }

  Value execute_function(CompilationUnit &unit, parser::node::FunctionCallNode *node) {

    auto callee = node->callee;

    SymbolId id = INVALID_SYMBOL_ID;
    if (node->callee->kind == core::node::NodeKind::PathExpression) {
      auto *path = static_cast<parser::node::statement::PathExprNode *>(node->callee);
      id = path->symbol_id;
    }

    if (id == INVALID_SYMBOL_ID) return Value::Null();

    auto symbol = unit.symbols.get(id);

    if (symbol->declaration && symbol->declaration->kind == core::node::NodeKind::NativeFunctionDeclaration) {
      auto *native = static_cast<core::node::NativeFunctionDeclarationNode *>(symbol->declaration);

      std::vector<Value> args;
      for (auto *arg : node->args) { args.push_back(execute_node(unit, arg)); }

      return native->callback(args);
    }

    return Value::Null();
  }

  void execute_ast(CompilationUnit &unit) {

    if (unit.diagns.all().size() > 0) { return; }
    for (auto &resolved_node : unit.ast.get_nodes()) { execute_node(unit, resolved_node); }
  }
};
