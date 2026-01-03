#include "DebugNode.hpp"
#include "core/node/Type.hpp"
#include "debug/console/color.hpp"
#include "debug/console/console.hpp"

static void debug_type(const core::node::TypeNode *type_node, const std::string &prefix, bool isLast) {
  using namespace debug;

  node::print_prefix(prefix, isLast);

  Console::log(Color::BrightBlue, "Type: ", Color::Purple, type_node->name);

  auto child_prefix = node::next_prefix(prefix, isLast);

  for (size_t i = 0; i < type_node->generics.size(); ++i) {
    bool isLastGeneric = (i + 1 == type_node->generics.size());
    node::debug_node(type_node->generics[i], child_prefix, isLastGeneric);
  }
}
