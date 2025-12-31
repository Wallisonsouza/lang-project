#pragma once
#include "core/node/Node.hpp"
#include <string>

namespace debug::node {
void debug_node(const core::node::Node *node, const std::string &prefix = "",
                bool isLast = true);

void print_prefix(const std::string &prefix, bool isLast);

std::string next_prefix(const std::string &prefix, bool isLast);

} // namespace debug::node
