#include "debug/console/color.hpp"
#include "debug/console/console.hpp"
#include "debug/engine/node/DebugNode.hpp"
#include "engine/parser/node/statement_nodes.hpp"
#include <string>

static void debug_function_call(const parser::node::FunctionCallNode *call_node,
                                const std::string &prefix, bool isLast) {

  using namespace debug;

  // 1. Imprime o próprio nó
  node::print_prefix(prefix, isLast);
  Console::log(Color::BrightBlue, "FunctionCall: ", Color::Purple);

  // 2. Calcula prefixo para os filhos
  auto child_prefix = node::next_prefix(prefix, isLast);

  // 3. Conta filhos reais
  int child_count = 0;
  if (call_node->callee) ++child_count;
  if (!call_node->args.empty()) ++child_count;

  int idx = 0;

  // 4. Imprime callee
  if (call_node->callee) {
    bool last_child = (++idx == child_count);
    node::debug_node(call_node->callee, child_prefix, last_child);
  }

  // 5. Imprime argumentos
  for (size_t i = 0; i < call_node->args.size(); ++i) {
    bool last_child = (++idx == child_count && i + 1 == call_node->args.size());
    node::debug_node(call_node->args[i], child_prefix, last_child);
  }
}
