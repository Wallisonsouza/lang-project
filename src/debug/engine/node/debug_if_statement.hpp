#pragma once
#include "DebugNode.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <string>

enum class GrafEdge { First, Middle, Last, Single };

inline std::string get_prefix(GrafEdge edge) {
  switch (edge) {
  case GrafEdge::First:
  case GrafEdge::Middle: return "├─ ";
  case GrafEdge::Last: return "└─ ";
  }
  return "";
}

inline std::string next_prefix(const std::string &current, GrafEdge edge) {
  switch (edge) {
  case GrafEdge::First:
  case GrafEdge::Middle: return current + "│ ";

  case GrafEdge::Last:
  case GrafEdge::Single: return current + " ";
  }
  return current;
}

static void debug_if_statement(const parser::node::IfStatementNode *node, const std::string &prefix, bool is_last) {
  auto edge = is_last ? GrafEdge::Last : GrafEdge::Middle;

  // print do nó
  debug::Console::log(debug::Color::BrightBlue, prefix, get_prefix(edge), "If");

  // prefixo herdado pelos filhos (apenas UMA vez)
  auto child_prefix = next_prefix(prefix, edge);

  if (node->condition) { debug::Console::log(child_prefix, get_prefix(GrafEdge::Middle), "Condition"); }

  if (node->then_body) {
    bool last_then = !node->else_body;

    debug::Console::log(child_prefix, get_prefix(last_then ? GrafEdge::Last : GrafEdge::Middle), "Then");

    debug::node::debug_node(node->then_body, child_prefix);
  }

  // if (node->else_body) {
  //   debug::Console::log(child_prefix, get_prefix(GrafEdge::Last), "Else");
  // }
}