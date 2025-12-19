#pragma once
#include "core/AST.hpp"
#include "core/node/Node.hpp"
#include "core/node/Type.hpp"
#include "debug/Color.hpp"
#include "debug/Console.hpp"
#include "parser/match/match_variable_declaration.hpp"
#include "parser/node/statement_nodes.hpp"
#include "parser/node/type_nodes.hpp"
#include "utils/Utf8.hpp"
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
inline std::string child_prefix(bool isLast) { return isLast ? "    " : "│   "; }
inline std::string connector(bool isLast) { return isLast ? "└─ " : "├─ "; }

inline void log_label_value(const std::string &prefix, bool isLast, const std::string &label, const std::string &value = "", Color labelColor = typeColor, Color valueColor_ = valueColor) {
  debug::Console::log(Color::BrightBlack, prefix, connector(isLast), labelColor, label, valueColor_, value);
}
inline void print_node(core::node::Node *node, const std::string &prefix, bool isLast);

template <typename NodeType> inline void print_node_list(const std::vector<NodeType *> &nodes, const std::string &prefix) {
  for (size_t i = 0; i < nodes.size(); ++i) print_node(nodes[i], prefix, i == nodes.size() - 1);
}

// ----------------------
// Função recursiva para imprimir nó
// ----------------------
inline void print_node(core::node::Node *node, const std::string &prefix = "", bool isLast = true) {
  if (!node) return;
  std::string childPrefix = prefix + child_prefix(isLast);

  // ---------------- TypeDeclarationNode ----------------
  if (auto td = dynamic_cast<core::node::TypeDeclarationNode *>(node)) {
    log_label_value(prefix, isLast, "TypeDeclaration: ", utils::Utf::utf32to8(td->name), typeColor, valueColor);
    for (size_t i = 0; i < td->type_params.size(); ++i) {
      bool lastParam = (i == td->type_params.size() - 1);
      log_label_value(childPrefix, lastParam, "Param", utils::Utf::utf32to8(td->type_params[i]), paramColor, valueColor);
    }
    return;
  }

  // ---------------- TypeNode ----------------
  if (auto type = dynamic_cast<node::TypeNode *>(node)) {
    std::string name = utils::Utf::utf32to8(type->name);
    if (!type->generics.empty()) name += "<>";
    log_label_value(prefix, isLast, "Type: ", name, typeColor, valueColor);
    print_node_list(type->generics, childPrefix);
    return;
  }

  // function params
  if (auto var = dynamic_cast<node::FunctionParameterNode *>(node)) {
    log_label_value(prefix, isLast, "FunctionParameter: ", utils::Utf::utf32to8(var->name), typeColor, valueColor);
    struct Child {
      std::string name;
      core::node::Node *node;
    };
    std::vector<Child> children = {{"Type", var->type}, {"Value", var->value}};
    for (size_t i = 0; i < children.size(); ++i) {
      auto &c = children[i];
      bool lastChild = (i == children.size() - 1);
      log_label_value(childPrefix, lastChild, c.name, ":");
      print_node(c.node, childPrefix + child_prefix(lastChild), true);
    }
    return;
  }

  // ---------------- VariableDeclarationNode ----------------
  if (auto var = dynamic_cast<node::VariableDeclarationNode *>(node)) {
    log_label_value(prefix, isLast, "VariableDeclaration: ", utils::Utf::utf32to8(var->name), typeColor, valueColor);
    struct Child {
      std::string name;
      core::node::Node *node;
    };

    log_label_value(childPrefix, false, "Modifiers: ", node::modifiersToString(var->modifiers));

    std::vector<Child> children = {{"Type", var->type}, {"Value", var->value}};
    for (size_t i = 0; i < children.size(); ++i) {
      auto &c = children[i];
      bool lastChild = (i == children.size() - 1);
      log_label_value(childPrefix, lastChild, c.name, ":");
      print_node(c.node, childPrefix + child_prefix(lastChild), true);
    }
    return;
  }

  // ---------------- FunctionDeclarationNode ----------------
  if (auto func = dynamic_cast<node::FunctionDeclarationNode *>(node)) {
    log_label_value(prefix, isLast, "FunctionDeclaration: ", utils::Utf::utf32to8(func->name), funcColor, valueColor);

    log_label_value(childPrefix, false, "Modifiers: ", node::modifiersToString(func->modifiers));

    debug::Console::log(Color::BrightBlack, childPrefix, connector(false), entry_color, "Params: ");
    for (size_t i = 0; i < func->parameters.size(); ++i) {
      bool lastParam = (i == func->parameters.size() - 1 && (!func->body || func->body->statements.empty()));
      print_node(func->parameters[i], childPrefix + child_prefix(lastParam), lastParam);
    }
    debug::Console::log(Color::BrightBlack, childPrefix, connector(false), entry_color, "Return: ");
    if (func->return_type) print_node(func->return_type, childPrefix + child_prefix(true), true);
    return;
  }

  // ---------------- BinaryExpressionNode ----------------
  if (auto bin = dynamic_cast<node::BinaryExpressionNode *>(node)) {
    log_label_value(prefix, isLast, "BinaryExpression: ", utils::Utf::utf32to8(bin->op), operatorColor, operatorColor);
    struct Child {
      std::string name;
      core::node::Node *node;
    };
    std::vector<Child> children = {{"Left", bin->left}, {"Right", bin->right}};
    for (size_t i = 0; i < children.size(); ++i) {
      bool lastChild = (i == children.size() - 1);
      log_label_value(childPrefix, lastChild, children[i].name, ":");
      print_node(children[i].node, childPrefix + child_prefix(lastChild), true);
    }
    return;
  }

  // ---------------- Outros nós ----------------
  if (auto id = dynamic_cast<node::VoidTypeNode *>(node)) {
    log_label_value(prefix, isLast, "VoidNode: ", utils::Utf::utf32to8(id->name), voidColor, voidColor);
    return;
  }

  if (auto id = dynamic_cast<node::IdentifierNode *>(node)) {
    log_label_value(prefix, isLast, "IdentifierNode: ", utils::Utf::utf32to8(id->name), identifierColor, valueColor);
    return;
  }

  if (auto num = dynamic_cast<node::NumberLiteralNode *>(node)) {
    log_label_value(prefix, isLast, "NumberLiteral: ", std::to_string(num->value), numberColor, numberColor);
    return;
  }

  if (auto str = dynamic_cast<node::StringLiteralNode *>(node)) {
    log_label_value(prefix, isLast, "StringLiteral: ", utils::Utf::utf32to8(str->value), stringColor, stringColor);
    return;
  }
}

// ----------------------
// Imprime toda a AST
// ----------------------
inline void print_ast(AST &ast) {
  for (auto *node : ast.get_nodes()) print_node(node);
}

} // namespace debug
