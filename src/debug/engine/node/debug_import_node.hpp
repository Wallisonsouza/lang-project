#pragma once
#include "DebugNode.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"
#include "utils/Utf8.hpp"

static void debug_import(const parser::node::statement::ImportNode *import_node, const std::string &prefix, bool isLast) {

  using namespace debug;
  using namespace debug::node;

  print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "ImportStatement");

  auto child_prefix = next_prefix(prefix, isLast);

  for (size_t i = 0; i < import_node->path.size(); ++i) {
    bool last = (i + 1 == import_node->path.size());
    print_prefix(child_prefix, last);
    Console::log(Color::Purple, "Module: ", utils::Utf::utf32to8(import_node->path[i]));
  }

  if (import_node->alias) {
    print_prefix(child_prefix, false);
    Console::log(Color::BrightCyan, "Alias:");

    if (import_node->alias.has_value()) { Console::log(utils::Utf::utf32to8(import_node->alias.value()), next_prefix(child_prefix, false), true); }
  }
}
