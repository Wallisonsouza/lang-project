#pragma once
#include "core/AST.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "debug/Color.hpp"
#include "debug/Console.hpp"
#include "parser/node/literal_nodes.hpp"
#include "parser/node/operator_nodes.hpp"
#include "parser/node/statement_nodes.hpp"
#include "utils/Utf8.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace debug {

// ----------------------
// Definição de cores
// ----------------------
inline const Color entry_color = Color(200, 200, 200);     // cinza claro
inline const Color typeColor = Color(102, 153, 255);       // azul pastel
inline const Color valueColor = Color(255, 153, 102);      // laranja pastel
inline const Color funcColor = Color(153, 255, 153);       // verde claro
inline const Color paramColor = Color(255, 204, 204);      // rosa suave
inline const Color operatorColor = Color(255, 204, 102);   // amarelo suave
inline const Color numberColor = Color(153, 204, 255);     // azul claro
inline const Color stringColor = Color(204, 153, 255);     // lilás pastel
inline const Color voidColor = Color(192, 192, 192);       // cinza neutro
inline const Color identifierColor = Color(255, 255, 153); // amarelo claro

// ----------------------
// Helpers para árvore
// ----------------------
inline std::string child_prefix(bool isLast) {
  return isLast ? "    " : "│   ";
}
inline std::string connector(bool isLast) { return isLast ? "└─ " : "├─ "; }

inline void log_label_value(const std::string &prefix, bool isLast,
                            const std::string &label,
                            const std::string &value = "",
                            Color labelColor = typeColor,
                            Color valueColor_ = valueColor) {
  debug::Console::log(Color::BrightBlack, prefix, connector(isLast), labelColor,
                      label, valueColor_, value);
}
inline void print_node(core::node::Node *node, const std::string &prefix,
                       bool isLast);

template <typename NodeType>
inline void print_node_list(const std::vector<NodeType *> &nodes,
                            const std::string &prefix) {
  for (size_t i = 0; i < nodes.size(); ++i)
    print_node(nodes[i], prefix, i == nodes.size() - 1);
}

// ----------------------
// Função recursiva para imprimir nó
inline void print_node(core::node::Node *node, const std::string &prefix = "",
                       bool isLast = true) {
  if (!node)
    return;

  std::string childPrefix = prefix + child_prefix(isLast);

  switch (node->kind) {

  case core::node::NodeKind::TypeDeclaration: {
    auto *td = static_cast<core::node::TypeDeclarationNode *>(node);
    log_label_value(prefix, isLast,
                    "TypeDeclaration: ", utils::Utf::utf32to8(td->name),
                    typeColor, valueColor);

    for (size_t i = 0; i < td->type_params.size(); ++i) {
      bool lastParam = (i == td->type_params.size() - 1);
      log_label_value(childPrefix, lastParam, "Param",
                      utils::Utf::utf32to8(td->type_params[i]), paramColor,
                      valueColor);
    }
    break;
  }

  case core::node::NodeKind::Type: {
    auto *type = static_cast<core::node::TypeNode *>(node);
    std::string name = utils::Utf::utf32to8(type->name);
    if (!type->generics.empty())
      name += "<>";
    log_label_value(prefix, isLast, "Type: ", name, typeColor, valueColor);
    print_node_list(type->generics, childPrefix);
    break;
  }

  case core::node::NodeKind::VariableDeclaration: {
    auto *var = static_cast<node::VariableDeclarationNode *>(node);

    log_label_value(prefix, isLast,
                    "VariableDeclaration: ", utils::Utf::utf32to8(var->name),
                    typeColor, valueColor);

    log_label_value(childPrefix, false, "Modifiers: ",
                    core::node::modifiersToString(var->modifiers));

    log_label_value(childPrefix, false, "Type:", "");
    print_node(var->type, childPrefix + child_prefix(false), true);

    log_label_value(childPrefix, true, "Value:", "");
    print_node(var->value, childPrefix + child_prefix(true), true);
    break;
  }

  case core::node::NodeKind::Identifier: {
    auto *id = static_cast<node::IdentifierNode *>(node);
    log_label_value(prefix, isLast,
                    "Identifier: ", utils::Utf::utf32to8(id->name),
                    identifierColor, valueColor);
    break;
  }

  case core::node::NodeKind::NumberLiteral: {
    auto *num = static_cast<node::NumberLiteralNode *>(node);
    log_label_value(prefix, isLast,
                    "NumberLiteral: ", std::to_string(num->value), numberColor,
                    numberColor);
    break;
  }

  case core::node::NodeKind::StringLiteral: {
    auto *str = static_cast<node::StringLiteralNode *>(node);
    log_label_value(prefix, isLast,
                    "StringLiteral: ", utils::Utf::utf32to8(str->value),
                    stringColor, stringColor);
    break;
  }

  case core::node::NodeKind::BinaryExpression: {
    auto *bin = static_cast<node::BinaryExpressionNode *>(node);

    log_label_value(prefix, isLast, "BinaryExpression: ",
                    core::node::binary_op_to_string(bin->op), operatorColor,
                    operatorColor);

    print_node(bin->left, childPrefix, false);
    print_node(bin->right, childPrefix, true);
    break;
  }

  case core::node::NodeKind::FunctionCall: {
    auto *function_call = static_cast<node::FunctionCallNode *>(node);

    log_label_value(prefix, isLast, "FunctionCall: ", "", typeColor,
                    valueColor);

    print_node(function_call->callee, childPrefix, false);

    print_node_list(function_call->args, childPrefix);
    break;
  }

  default:
    log_label_value(prefix, isLast, "UnknownNode", "", entry_color,
                    entry_color);
    break;
  }
}

// ----------------------
// Imprime toda a AST
// ----------------------
inline void print_ast(AST &ast) {

  Console::log("ast size: ", ast.size());
  for (auto *node : ast.get_nodes())
    print_node(node);
}

} // namespace debug
