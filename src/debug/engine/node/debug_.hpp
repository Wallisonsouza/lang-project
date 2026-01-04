#include "DebugNode.hpp"
#include "core/node/Type.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "engine/parser/node/statement/ImportStatement.hpp"

static void
debug_expression_statement(const core::node::ExpressionStatementNode *node,
                           const std::string &prefix, bool isLast) {
  using namespace debug;

  node::print_prefix(prefix, isLast);

  Console::log(Color::BrightBlue, "ExpressionStatement: ", Color::Purple);

  auto child_prefix = node::next_prefix(prefix, true);
  node::debug_node(node->expr, child_prefix, true);
}

static void
debug_assing_node(const parser::node::statement::AssignmentNode *node,
                  const std::string &prefix, bool isLast) {
  using namespace debug;

  node::print_prefix(prefix, isLast);

  Console::log(Color::BrightBlue, "Assignment: ", Color::Purple);

  auto child_prefix = node::next_prefix(prefix, true);
  node::debug_node(node->target, child_prefix, false);
  node::debug_node(node->value, child_prefix, true);
}
