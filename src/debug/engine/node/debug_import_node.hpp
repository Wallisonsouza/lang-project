#pragma once
#include "DebugNode.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

static void debug_path_expr(const parser::node::statement::PathExprNode *node,
                            const std::string &prefix, bool isLast) {

  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(debug::Color::BrightBlue, "Path");

  auto child_prefix = debug::node::next_prefix(prefix, isLast);

  for (size_t i = 0; i < node->segments.size(); ++i) {
    bool last = (i + 1 == node->segments.size());

    debug::node::debug_node(node->segments[i], child_prefix, last);
  }
}

static void debug_import(const parser::node::statement::ImportNode *import_node,
                         const std::string &prefix, bool isLast) {

  using namespace debug;
  using namespace debug::node;

  print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "Import");

  auto child_prefix = next_prefix(prefix, isLast);

  for (size_t i = 0; i < import_node->path.size(); ++i) {
    bool last = (i + 1 == import_node->path.size());
    debug_node(import_node->path[i], child_prefix, last);
  }

  if (import_node->alias) {
    print_prefix(child_prefix, false);
    Console::Console::log(Color::BrightCyan, "Alias:");
    Console::log(import_node->alias.value(), next_prefix(child_prefix, false),
                 true);
  }
}
