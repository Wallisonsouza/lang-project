#include "DebugNode.hpp"
#include "core/node/NodeKind.hpp"
#include "core/node/Type.hpp"
#include "debug/engine/node/debug_import_node.hpp"
#include "debug/engine/node/debug_member_access.hpp"
#include "debug_function_call.hpp"
#include "debug_literals.hpp"
#include "debug_type.hpp"
#include "debug_variable_declaration.hpp"
#include "engine/parser/node/literal_nodes.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <iostream>
using namespace core::node;

namespace debug::node {

void print_prefix(const std::string &prefix, bool isLast) {
  std::cout << prefix;
  std::cout << (isLast ? "└─ " : "├─ ");
}

std::string next_prefix(const std::string &prefix, bool isLast) {
  return prefix + (isLast ? "   " : "│  ");
}

inline void debug_node(const core::node::Node *node, const std::string &prefix,
                       bool isLast) {
  if (!node) return;

  switch (node->kind) {
  // Literais
  case NodeKind::NumberLiteral:
    debug_number_literal(
        static_cast<const parser::node::NumberLiteralNode *>(node), prefix,
        isLast);
    break;
  case NodeKind::StringLiteral:
    debug_string_literal(
        static_cast<const parser::node::StringLiteralNode *>(node), prefix,
        isLast);
    break;
  case NodeKind::BoolLiteral:
    debug_bool_literal(static_cast<const parser::node::BoolLiteralNode *>(node),
                       prefix, isLast);
    break;
  case NodeKind::CharLiteral:
    debug_char_literal(static_cast<const parser::node::CharLiteralNode *>(node),
                       prefix, isLast);
    break;
  case NodeKind::NullLiteral:
    debug_null_literal(static_cast<const parser::node::NullLiteralNode *>(node),
                       prefix, isLast);
    break;
  case NodeKind::Identifier:
    debug_identifier(static_cast<const parser::node::IdentifierNode *>(node),
                     prefix, isLast);
    break;
  case NodeKind::MemberAccess:
    debug_member_access(
        static_cast<const parser::node::MemberAccessNode *>(node), prefix,
        isLast);
    break;
  case NodeKind::ImportStatement:
    debug_import(static_cast<const parser::node::statement::ImportNode *>(node),
                 prefix, isLast);
    break;
  case NodeKind::Type:
    debug_type(static_cast<const TypeNode *>(node), prefix, isLast);
    break;
  case NodeKind::VariableDeclaration:
    debug_variable_declaration(
        static_cast<const parser::node::VariableDeclarationNode *>(node),
        prefix, isLast);
    break;
  case NodeKind::FunctionDeclaration:
    // debug_function_declaration(
    //     static_cast< const parser::node::FunctionDeclarationNode *>(node),
    //     prefix, isLast);
    break;
  case NodeKind::FunctionCall:
    debug_function_call(
        static_cast<const parser::node::FunctionCallNode *>(node), prefix,
        isLast);
    break;

  default:
    print_prefix(prefix, isLast);
    std::cout << "<unknown node>\n";
    break;
  }
}

} // namespace debug::node
