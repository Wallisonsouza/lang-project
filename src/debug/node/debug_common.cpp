#pragma once
#include "core/node/Node.hpp"

#include <string>

namespace debug::node {

inline void print_node(core::node::Node *node, const std::string &prefix,
                       bool isLast);
} // namespace debug::node
