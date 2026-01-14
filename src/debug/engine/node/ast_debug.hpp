#pragma once
#include "core/AST.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/operator_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <string>
#include <vector>

struct TreeLayout {
  std::ostream &out;
  std::vector<bool> ancestors_alive;

  explicit TreeLayout(std::ostream &out);

  void begin_node(bool is_last);
  void end_node();
  void print_vertical_padding(size_t lines);
};

struct ASTDebug {

  struct LabeledChild {
    const char *label;
    const core::node::Node *node;
  };

  debug::Color label_color = debug::Color::Blue;
  debug::Color header_color = debug::Color::Purple;

  void debug_labeled_children(const char *label, const std::vector<LabeledChild> &children, bool is_last) {
    tree.begin_node(is_last);
    out << label << "\n";

    for (size_t i = 0; i < children.size(); ++i) {
      const auto &child = children[i];
      bool child_is_last = (i + 1 == children.size());

      tree.begin_node(child_is_last);
      out << child.label << "\n";
      debug_node(child.node, true);
      tree.end_node();
    }

    tree.end_node();
  }

  void debug_header(const std::string &header) { debug::Console::log(header_color, header); }

  std::ostream &out;
  TreeLayout tree;

  explicit ASTDebug(std::ostream &out = std::cout);

  void dump_ast(const AST &ast);
  void debug_labeled(const char *label, const core::node::Node *child, bool is_last);

  void debug_node(const core::node::Node *node, bool is_last);

  void debug_number_literal(const parser::node::NumberLiteralNode *node);
  void debug_funtion_parameter(const core::node::FunctionParameterNode *node);
  void debug_string_literal(const parser::node::StringLiteralNode *node);
  void debug_bool_literal(const parser::node::BoolLiteralNode *node);
  void debug_char_literal(const parser::node::CharLiteralNode *node);
  void debug_null_literal(const parser::node::NullLiteralNode *node);
  void debug_identifier(const core::node::IdentifierNode *node);
  void debug_member_access(const parser::node::MemberAccessNode *node);
  void debug_import(const parser::node::statement::ImportNode *node);
  void debug_type(const core::node::TypeNode *node);
  void debug_variable_declaration(const parser::node::VariableDeclarationNode *node);
  void debug_binary_expression(const parser::node::BinaryExpressionNode *node);
  void debug_function_call(const parser::node::FunctionCallNode *node);
  void debug_expression_statement(const core::node::ExpressionStatementNode *node);

  void debug_return_statement(const parser::node::ReturnStatementNode *node);

  void debug_native_function_declaration(const core::node::NativeFunctionDeclarationNode *node);
  void debug_function_declaration(const parser::node::FunctionDeclarationNode *node);
  void debug_index_acess(const parser::node::IndexAccessNode *node);

  void debug_path_expression(const parser::node::statement::PathExprNode *node);
  void debug_if_statement(const parser::node::IfStatementNode *node);
  void debug_assing_node(const parser::node::statement::AssignmentNode *node);
  void debug_block(const parser::node::BlockStatementNode *node);

  void debug_children(const std::vector<const core::node::Node *> &children);

  template <typename T> void debug_labeled_childrens(const std::vector<T *> &children, const std::string &label, bool is_last) {

    tree.begin_node(is_last);

    debug::Console::log(label_color, label);

    size_t count = 0;
    for (auto *c : children)
      if (c) ++count;

    size_t printed = 0;
    for (auto *c : children) {
      if (!c) continue;
      ++printed;
      bool child_is_last = (printed == count);
      debug_node(c, child_is_last);
    }

    tree.end_node();
  }
};