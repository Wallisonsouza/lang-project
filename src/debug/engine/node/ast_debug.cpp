#include "ast_debug.hpp"
#include "core/AST.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement_nodes.hpp"

ASTDebug::ASTDebug(std::ostream &out) : out(out), tree(out) {}

TreeLayout::TreeLayout(std::ostream &out) : out(out) {}

void TreeLayout::begin_node(bool is_last) {

  for (bool alive : ancestors_alive) { out << (alive ? "│  " : "   "); }

  out << (is_last ? "└─ " : "├─ ");

  ancestors_alive.push_back(!is_last);
}

void TreeLayout::end_node() { ancestors_alive.pop_back(); }

void ASTDebug::debug_node(const core::node::Node *node, bool isLast) {
  using namespace core::node;
  if (!node) return;

  tree.begin_node(isLast);

  switch (node->kind) {

  case NodeKind::NumberLiteral: debug_number_literal(static_cast<const parser::node::NumberLiteralNode *>(node)); break;

  case NodeKind::StringLiteral: debug_string_literal(static_cast<const parser::node::StringLiteralNode *>(node)); break;

  case NodeKind::BooleanLiteral: debug_bool_literal(static_cast<const parser::node::BoolLiteralNode *>(node)); break;

  case NodeKind::CharLiteral: debug_char_literal(static_cast<const parser::node::CharLiteralNode *>(node)); break;

  case NodeKind::NullLiteral: debug_null_literal(static_cast<const parser::node::NullLiteralNode *>(node)); break;

  case NodeKind::Identifier: debug_identifier(static_cast<const IdentifierNode *>(node)); break;

  case NodeKind::Import: debug_import(static_cast<const parser::node::statement::ImportNode *>(node)); break;

  case NodeKind::Type: debug_type(static_cast<const TypeNode *>(node)); break;

  case NodeKind::VariableDeclaration: debug_variable_declaration(static_cast<const parser::node::VariableDeclarationNode *>(node)); break;

  case NodeKind::BinaryExpression: debug_binary_expression(static_cast<const parser::node::BinaryExpressionNode *>(node)); break;

  case NodeKind::FunctionCall: debug_function_call(static_cast<const parser::node::FunctionCallNode *>(node)); break;

  case NodeKind::ExpressionStatement: debug_expression_statement(static_cast<const ExpressionStatementNode *>(node)); break;

  case NodeKind::FunctionDeclaration: debug_function_declaration(static_cast<const parser::node::FunctionDeclarationNode *>(node)); break;

  case NodeKind::PathExpression: debug_path_expression(static_cast<const parser::node::statement::PathExprNode *>(node)); break;

  case NodeKind::IfExpression: debug_if_statement(static_cast<const parser::node::IfExpressionNode *>(node)); break;

  case NodeKind::Assignment: debug_assing_node(static_cast<const parser::node::statement::AssignmentNode *>(node)); break;

  case NodeKind::BlockExpression: debug_block(static_cast<const parser::node::BlockExpressionNode *>(node)); break;

  case NodeKind::FunctionParameter: debug_funtion_parameter(static_cast<const FunctionParameterNode *>(node)); break;

  default: out << "<unknown>\n"; break;
  }

  tree.end_node();
}

void ASTDebug::dump_ast(const AST &ast) {

  tree.ancestors_alive.clear();

  for (size_t i = 0; i < ast.size(); ++i) {
    bool is_last = (i + 1 == ast.size());
    debug_node(ast.get_nodes()[i], is_last);
  }
}

// void ASTDebug::debug_children(const std::vector<const core::node::Node *> &children) {

//   size_t count = 0;
//   for (auto *c : children)
//     if (c) ++count;

//   size_t printed = 0;
//   for (auto *c : children) {
//     if (!c) continue;
//     ++printed;
//     bool is_last = (printed == count);
//     debug_node(c, is_last);
//   }
// }

void ASTDebug::debug_labeled(const char *label, const core::node::Node *child, bool is_last) {
  tree.begin_node(is_last);

  debug::Console::log(debug::Color::Blue, label);

  if (child) { debug_node(child, true); }

  tree.end_node();
}
