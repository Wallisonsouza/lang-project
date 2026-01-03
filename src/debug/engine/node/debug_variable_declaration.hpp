#include "DebugNode.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement_nodes.hpp"

static void debug_variable_declaration(const parser::node::VariableDeclarationNode *var, const std::string &prefix, bool isLast) {
  debug::node::print_prefix(prefix, isLast);
  debug::Console::log(debug::Color::BrightBlue, "VariableDeclaration: ", debug::Color::Purple, var->name);

  auto child_prefix = debug::node::next_prefix(prefix, isLast);

  if (var->type) { debug::node::debug_node(var->type, child_prefix, false); }

  if (var->value) { debug::node::debug_node(var->value, child_prefix, true); }
}
